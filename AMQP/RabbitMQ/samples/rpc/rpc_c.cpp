#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>
void die_on_amqp_error(amqp_rpc_reply_t x, char const *context)
{
	switch (x.reply_type)
	{
	case AMQP_RESPONSE_NORMAL:
		return;

	case AMQP_RESPONSE_NONE:
		fprintf(stderr, "%s: missing RPC reply type!\n", context);
		break;

	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
		break;

	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (x.reply.id)
		{
		case AMQP_CONNECTION_CLOSE_METHOD:
		{
			amqp_connection_close_t *m =
				(amqp_connection_close_t *)x.reply.decoded;
			fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
				context, m->reply_code, (int)m->reply_text.len,
				(char *)m->reply_text.bytes);
			break;
		}
		case AMQP_CHANNEL_CLOSE_METHOD:
		{
			amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
			fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
				context, m->reply_code, (int)m->reply_text.len,
				(char *)m->reply_text.bytes);
			break;
		}
		default:
			fprintf(stderr, "%s: unknown server error, method id 0x%08X\n",
				context, x.reply.id);
			break;
		}
		break;
	}

}


int main(int argc, char const *const *argv)
{
	char const * host = "192.168.119.129";
	int port = 5672, status;
	char const * exchange = "rpc_exchange";
	char const * queue = "rpcqueue";
	char const * bindingkey = "rpc";
	char const * exchangetype = "direct"; //direct, topic,fanout, headers
	amqp_socket_t * socket = NULL;
	amqp_connection_state_t conn;
	char const * messagebody = "return hello word";


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
		die_on_amqp_error(amqp_get_rpc_reply(conn), "");
		return -1;
	}

	amqp_basic_consume(conn, 1, amqp_cstring_bytes(queue), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		die_on_amqp_error(amqp_get_rpc_reply(conn), "");
		return -1;
	}

	amqp_queue_bind(conn, 1, amqp_cstring_bytes(queue),
		amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey),
		amqp_empty_table);

	if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
	{
		die_on_amqp_error(amqp_get_rpc_reply(conn),"");
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
	
			printf("Delivery %u, exchange %.*s ,routingkey %.*s ,reply routingkey %.*s\n",
					(unsigned)envelope.delivery_tag,
					(int)envelope.exchange.len,
					(char *)envelope.exchange.bytes,
					(int)envelope.routing_key.len,
					(char *)envelope.routing_key.bytes,
					(char *)envelope.message.properties.reply_to.len,
					(char *)envelope.message.properties.reply_to.bytes);

			printf("----\n");

			printf("data: %.*s \n", envelope.message.body.len, (char*)envelope.message.body.bytes);

			printf("----\n");

			amqp_basic_properties_t props;
			props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG |
							AMQP_BASIC_DELIVERY_MODE_FLAG |
							AMQP_BASIC_CORRELATION_ID_FLAG;
			props.content_type = amqp_cstring_bytes("text/plain");
			props.delivery_mode = 2; // persistent delivery mode
		
			props.correlation_id = amqp_cstring_bytes("1");

			amqp_basic_publish(conn,1,amqp_empty_bytes,amqp_cstring_bytes((char *)envelope.message.properties.reply_to.bytes),
								0,0,&props,amqp_cstring_bytes(messagebody));

			printf("return data: %s\n", messagebody);

			//amqp_bytes_free(props.reply_to);

			printf("end send \n");
			amqp_destroy_envelope(&envelope);
		}
	}

	amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(conn);

	return 0;
}
