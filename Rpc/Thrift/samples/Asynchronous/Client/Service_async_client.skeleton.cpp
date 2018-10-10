#include "Service.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <thrift/stdcxx.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/Thread.h>
#include <thrift/async/TAsyncChannel.h>
#include <thrift/async/TEvhttpClientChannel.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TProtocol.h>
#include <event.h>



using namespace  ::apache::thrift;
using namespace  ::apache::thrift::transport;
using namespace  ::apache::thrift::protocol;
using namespace  ::apache::thrift::async;
using namespace  ::apache::thrift::concurrency;
using namespace  ::test::stress;

class MyClient : public ServiceCobClient
{
public:
	MyClient(stdcxx::shared_ptr<TAsyncChannel> channel, TProtocolFactory* protocolFactory)
		: ServiceCobClient(channel, protocolFactory)
	{

	}
	virtual ~MyClient(){}

	virtual void completed__(bool success)
	{
		if (success)
		{
			std::cout << "completed" << std::endl;
		}
		else
		{
			std::cout << "completed failed" << std::endl;
		}
	}

	void my_send_byte()
	{
		std::cout << "begin my_send_byte" << std::endl;
		stdcxx::function<void(ServiceCobClient*)> cob = stdcxx::bind(&MyClient::recv_byte_callback, this, stdcxx::placeholders::_1);
		echoByte(cob, 'A');
		std::cout << "end my_send_byte" << std::endl;
	}

	void my_send_string()
	{
		std::cout << "begin my_send_string" << std::endl;
		stdcxx::function<void(ServiceCobClient*)> cob = stdcxx::bind(&MyClient::recv_string_callback, this, stdcxx::placeholders::_1);
		echoString(cob, "test asynclient");
		std::cout << "end my_send_string" << std::endl;
	}

	void recv_byte_callback(ServiceCobClient* client)
	{
		std::cout << "recv_byte_callback" << std::endl;
	    _res_byte = recv_echoByte();
		std::cout << "_res_byte =" << _res_byte << std::endl;
	}

	void recv_string_callback(ServiceCobClient* client)
	{
		std::cout << "recv_string_callback" << std::endl;
		recv_echoString(_res_string);
		std::cout << "_res_string=" << _res_string << std::endl;
	}
private:
	char _res_byte;
	std::string _res_string;
};

class ClientThread : public Runnable
{
public:
	ClientThread(event_base* base, std::string & host, int port)
		: _base(base), _host(host), _port(port)
	{
	}
	virtual ~ClientThread(){}
	virtual void run()
	{
		stdcxx::shared_ptr<TAsyncChannel>  channel1(new TEvhttpClientChannel(_host, "/", _host.c_str(), _port, _base));
		stdcxx::shared_ptr<TAsyncChannel>  channel2(new TEvhttpClientChannel(_host, "/", _host.c_str(), _port, _base));

		MyClient client1(channel1, new TBinaryProtocolFactory());
		MyClient client2(channel2, new TBinaryProtocolFactory());

		client1.my_send_byte();
		client1.my_send_string();

		client2.my_send_byte();
		client2.my_send_string();

		while (1)
		{
			client1.my_send_byte();
			sleep(1);
		}
	}
protected:
private:
	event_base* _base;
	std::string _host;
	int _port;
};

int main()
{
	std::string host = "192.168.119.129";
	int port = 9999;

	event_base* base = event_base_new();

	stdcxx::shared_ptr<PlatformThreadFactory> threadFactory = std::shared_ptr<PlatformThreadFactory>(new PlatformThreadFactory());
	stdcxx::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(10);

	threadManager->threadFactory(threadFactory);
	threadManager->start();

	stdcxx::shared_ptr<Thread> thread = threadFactory->newThread(std::shared_ptr<ClientThread>(new ClientThread(base, host, port)));
	thread->start();

	event_base_dispatch(base);
	event_base_free(base);

	return 0;
}