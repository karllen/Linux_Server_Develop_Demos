
#include <iostream>
#include <string>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "Service.h"

using namespace  ::test::stress;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main()
{
	::apache::thrift::stdcxx::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	::apache::thrift::stdcxx::shared_ptr<TTransport> transport(new TFramedTransport(socket));
	::apache::thrift::stdcxx::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	ServiceClient client(protocol);

	transport->open();

	std::cout << "client echoByte byte=" << client.echoByte('A') << std::endl;

	std::cout << "send_echoByte('B')" << std::endl;
	client.send_echoByte('B');
	std::cout << "send_echoByte('C')" << std::endl;
	client.send_echoByte('C');

	std::cout << "recv_echoByte()" << client.recv_echoByte() << std::endl;
	std::cout << "recv_echoByte()" << client.recv_echoByte() << std::endl;

	transport->close();

	return 0;
}

