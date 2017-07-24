#ifndef _PACKETS_H
#define _PACKETS_H

#define MAX_NAME_SIZE 10

void tostruct(char *);
//void fillstruct(char *);
//void fillstruct(char packet_type ,char *sended_data, int *packet_size)

enum {
   QUERY_BROADCAST,
   QUERY_UNICAST,
   HELLO_RESPONSE,
   CHAT,
   CHAT_ACK,
   EXITING,
} EN_PACKET;

struct discovery_broadcast
{
	char type;
	char requester_name[10];
	char requester_surname[10];
} __attribute__((packed));
struct discovery_unicast
{
	char type;
	char requester_name[10];
	char requester_surname[10];
	char target_name[10];
	char target_surname[10];
} __attribute__((packed));
struct hello_response
{
	char type;
	char responder_name[10];
	char responder_surname[10];
	char queryier_name[10];
	char queryier_surname[10];
} __attribute__((packed));
struct chat
{
	char type;
	short length;
	char packet_id;
	char message[100];
} __attribute__((packed));
struct chat_ACK
{
	char type;
	char packet_id;
} __attribute__((packed));
struct exiting
{
	char type;
	char name[10];
	char surname[10];
} __attribute__((packed));

#endif 




