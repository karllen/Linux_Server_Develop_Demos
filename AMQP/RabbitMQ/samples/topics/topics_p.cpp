#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <string>

int main()
{
	const char * host = "192.168.119.129";
	const char * exchange = "topic_exchange";

	int port = 5672, status;
	std::string messages[5] = { "first", "second", "third", "fourth", "five" };
	std::string routingkeys[5] = {"xxoo.test.xxoo","xxoo.xxoo.test2","lazy.xxoo","lazy.xxoo2","xx"};
	std::string messagebody = "message";
	amqp_socket_t * socket = NULL;
	amqp_connection_state_t conn;

	conn = amqp_new_connection();

	socket = amqp_tcp_socket_new(conn);

	if (!socket)
	{
		return -1;
	}

	status = amqp_socket_open(socket, host, port);

	if (status < 0)
	{
		return -1;
	}

	amqp_rpc_reply_t r = amqp_login(conn, "/", 0, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "karllen", "123456");

	if (r.reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	amqp_channel_open(conn, 1);

	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	amqp_basic_properties_t props;
	props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
	props.content_type = amqp_cstring_bytes("text/plain");
	props.delivery_mode = 2;
	for (int i = 0; i < 5; i++)
	{
		std::string body = messages[i] + messagebody;
		const char * routingkey = routingkeys[i].c_str();
		if (amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange), amqp_cstring_bytes(routingkey), 0, 0,
			&props, amqp_cstring_bytes(body.c_str())) < 0)
		{
			return -1;
		}
	}


	if (amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	if (amqp_connection_close(conn, AMQP_REPLY_SUCCESS).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	if (amqp_destroy_connection(conn) < 0)
	{
		return -1;
	}

	return 0;
}
