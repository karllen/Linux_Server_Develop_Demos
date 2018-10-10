#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <amqp.h>
#include <amqp_tcp_socket.h>


int main(int argc, char *argv[]) 
{
	char const * host = "192.168.119.129";
	int port = 5672, status;
	char const * exchange = "rpc_exchange";
	char const * routingkey = "rpc";
	char const * messagebody = "hello word";
	char const * reply_queue = "replyqueue";
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

	{
		amqp_queue_declare_ok_t *r = amqp_queue_declare(
			conn, 1, amqp_cstring_bytes(reply_queue), 0, 1, 0, 0, amqp_empty_table);
		if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
		{
			return -1;
		}
	}

	
	{
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG |
			AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_REPLY_TO_FLAG |
			AMQP_BASIC_CORRELATION_ID_FLAG;
		props.content_type = amqp_cstring_bytes("text/plain");
		props.delivery_mode = 2; /* persistent delivery mode */
		props.reply_to = amqp_bytes_malloc_dup(amqp_cstring_bytes(reply_queue)); //routingkey
		if (props.reply_to.bytes == NULL) 
		{
			fprintf(stderr, "Out of memory while copying queue name");
			return 1;
		}
		props.correlation_id = amqp_cstring_bytes("1");

		amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange),
							amqp_cstring_bytes(routingkey), 0, 0,
							&props, amqp_cstring_bytes(messagebody));

		amqp_bytes_free(props.reply_to);
	}

	{
		amqp_basic_consume(conn, 1, amqp_cstring_bytes(reply_queue), amqp_empty_bytes, 0, 1, 0,
							amqp_empty_table);

		if (amqp_get_rpc_reply(conn).reply_type != AMQP_RESPONSE_NORMAL)
		{
			return -1;
		}

		{
			amqp_frame_t frame;
			int result;

			amqp_basic_deliver_t *d;
			amqp_basic_properties_t *p;
			size_t body_target;
			size_t body_received;

			for (;;) 
			{
				amqp_maybe_release_buffers(conn);
				result = amqp_simple_wait_frame(conn, &frame);
				printf("Result: %d\n", result);
				if (result < 0) 
				{
					break;
				}

				printf("Frame type: %u channel: %u\n", frame.frame_type, frame.channel);
				if (frame.frame_type != AMQP_FRAME_METHOD) 
				{
					continue;
				}

				printf("Method: %s\n", amqp_method_name(frame.payload.method.id));
				if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD) 
				{
					continue;
				}

				d = (amqp_basic_deliver_t *)frame.payload.method.decoded;
				printf("Delivery: %u exchange: %.*s routingkey: %.*s\n",
					(unsigned)d->delivery_tag, (int)d->exchange.len,
					(char *)d->exchange.bytes, (int)d->routing_key.len,
					(char *)d->routing_key.bytes);

				result = amqp_simple_wait_frame(conn, &frame);
				if (result < 0) 
				{
					break;
				}

				if (frame.frame_type != AMQP_FRAME_HEADER) 
				{
					fprintf(stderr, "Expected header!");
					abort();
				}
				p = (amqp_basic_properties_t *)frame.payload.properties.decoded;
				if (p->_flags & AMQP_BASIC_CONTENT_TYPE_FLAG) 
				{
					printf("Content-type: %.*s\n", (int)p->content_type.len,
						(char *)p->content_type.bytes);
				}
				printf("----\n");

				body_target = (size_t)frame.payload.properties.body_size;
				body_received = 0;

				printf("recv reply data:");
				while (body_received < body_target) 
				{
					result = amqp_simple_wait_frame(conn, &frame);
					if (result < 0) 
					{
						break;
					}

					if (frame.frame_type != AMQP_FRAME_BODY) 
					{
						fprintf(stderr, "Expected body!");
						abort();
					}

					body_received += frame.payload.body_fragment.len;

					printf("%.*s", frame.payload.body_fragment.len, frame.payload.body_fragment.bytes);
				}

				if (body_received != body_target) 
				{
					/* Can only happen when amqp_simple_wait_frame returns <= 0 */
					/* We break here to close the connection */
					break;
				}
				printf("\nrecv reply end \n");
				/* everything was fine, we can quit now because we received the reply */
				break;
			}
		}
	}

	amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);

	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);

	amqp_destroy_connection(conn);

	return 0;




}
