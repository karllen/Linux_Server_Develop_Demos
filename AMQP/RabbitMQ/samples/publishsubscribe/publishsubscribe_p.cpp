#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <string>
#include <stdio.h>

int main()
{
	const char * host = "192.168.119.129";
	const char * exchange = "publishsubscribe_exchange";
	const char * routingkey = "publishsubscribe";

	int port = 5672, status;
	std::string messages[5] = { "first", "second", "third", "fourth", "five" };
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
	
	amqp_confirm_select(conn, 1);
	for (int i = 0; i < 5; i++)
	{
		std::string body = messages[i] + messagebody;
		if (amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange), amqp_cstring_bytes(routingkey), 0, 0,
			&props, amqp_cstring_bytes(body.c_str())) < 0)
		{
			return -1;
		}
		amqp_frame_t frame;
		amqp_rpc_reply_t r;
		if (AMQP_STATUS_OK != amqp_simple_wait_frame(conn, &frame))
		{
			return -1;
		}
		if (frame.frame_type == AMQP_FRAME_METHOD)
		{
			amqp_method_t method = frame.payload.method;

			printf("method id=%08X, method name=%s",
				method.id, amqp_method_name(method.id));

			switch (method.id)
			{
			case AMQP_BASIC_ACK_METHOD:
			{
				amqp_basic_ack_t * ack = (amqp_basic_ack_t*) method.decoded;

				printf("ack.delivery_tag=%d\n", ack->delivery_tag);
				printf("ack.multiple=%d\n", ack->multiple);
				break;
			}
			case  AMQP_BASIC_NACK_METHOD:
			{
				amqp_basic_nack_t * nack =(amqp_basic_nack_t *)method.decoded;
				printf("nack.delivery_tag=%d\n", nack->delivery_tag);
				printf("nack.multiple=%d\n", nack->multiple);
				printf("nack.requeue=%d\n", nack->requeue);
				break;
			}
			case AMQP_BASIC_RETURN_METHOD:
			{
				amqp_message_t message;
				amqp_basic_return_t *basic_ret = (amqp_basic_return_t *)method.decoded;
				printf("return.reply_code=%d\n", basic_ret->reply_code);
				printf("return.reply_text=%.*s\n", basic_ret->reply_text.len, basic_ret->reply_text.bytes);

				r = amqp_read_message(conn, frame.channel, &message, 0);
				if (AMQP_RESPONSE_NORMAL != r.reply_type)
				{
					return -1;
				}

				printf("message.body.bytes=%.*s\n", message.body.len, message.body.bytes);
				amqp_destroy_message(&message);

				break;
			}
			case AMQP_CHANNEL_CLOSE_METHOD:
			{
				printf("channel close method\n");
				break;
			}
			case AMQP_CONNECTION_CLOSE_METHOD:
			{
				printf("connection close method\n");
				break;
			}

			default:

				printf("An unexpected method was received %d\n", method.id);
				break;
			}
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
