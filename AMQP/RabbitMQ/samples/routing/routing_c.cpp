
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *const *argv)
{
	const char * host = "192.168.119.129";
	const char * exchange = "routing_exchange";
	const char * exchangetype = "direct"; //direct, topic,fanout, headers
	std::string bindingkeys[5] = { "first", "second", "third", "fourth", "five" };
	
	const char *  queue = argv[1];
	//bind 1: "second", "third", "fourth", "five"
	//bind 0: "first"
	int bind = atoi((char*)argv[2]);
	
	amqp_socket_t * socket = NULL;
	amqp_connection_state_t conn;

	int port = 5672, status;

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

	amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange),
		amqp_cstring_bytes(exchangetype), 0, 1, 0, 0,
		amqp_empty_table);

	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	amqp_queue_declare(conn, 1, amqp_cstring_bytes(queue), 0, 1, 0, 0, amqp_empty_table);
	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	if (bind == 0){
		amqp_queue_bind(conn, 1, amqp_cstring_bytes(queue),
			amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkeys[0].c_str()),
			amqp_empty_table);

		if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
		{
			return -1;
		}
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			amqp_queue_bind(conn, 1, amqp_cstring_bytes(queue),
				amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkeys[i].c_str()),
				amqp_empty_table);

			if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
			{
				return -1;
			}
		}
	}

	//amqp_queue_unbind(conn, 1, amqp_cstring_bytes(queue),
	//	amqp_cstring_bytes(exchange),
	//	amqp_cstring_bytes(bindingkey), amqp_empty_table);

	amqp_basic_consume(conn, 1, amqp_cstring_bytes(queue), amqp_empty_bytes, 0, 1, 0,
		amqp_empty_table);

	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		return -1;
	}

	{
		for (;;)
		{
			amqp_rpc_reply_t res;
			amqp_envelope_t envelope;

			amqp_maybe_release_buffers(conn);

			res = amqp_consume_message(conn, &envelope, NULL, 0);

			if (AMQP_RESPONSE_NORMAL != res.reply_type)
			{
				break;
			}

			printf("Delivery %u, exchange %.*s routingkey %.*s\n",
				(unsigned)envelope.delivery_tag, (int)envelope.exchange.len,
				(char *)envelope.exchange.bytes, (int)envelope.routing_key.len,
				(char *)envelope.routing_key.bytes);

			if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG)
			{
				printf("Content-type: %.*s\n",
					(int)envelope.message.properties.content_type.len,
					(char *)envelope.message.properties.content_type.bytes);
			}

			printf("----\n");

			printf("data len:%.*s", (int)envelope.message.body.len, (char*)envelope.message.body.bytes);

			printf("\n");
			amqp_destroy_envelope(&envelope);
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