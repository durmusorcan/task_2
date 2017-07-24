/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include "packets.h"

#define MY_DEST_MAC0	0xFF
#define MY_DEST_MAC1	0xFF
#define MY_DEST_MAC2	0xFF
#define MY_DEST_MAC3	0xFF
#define MY_DEST_MAC4	0xFF
#define MY_DEST_MAC5	0xFF

#define DEFAULT_IF	"enp14s0"
#define BUF_SIZ		1024

#define MY_NAME "durmus"
#define MY_SURNAME "orcan"

#define TARGET_NAME "odul"
#define TARGET_SURNAME "kivrak"

#define MESSAGE "merhabaaaaaaaaaaaaaaa"
#define LENGHT 0x19
#define PACKET_ID 0x01
//int fillstruct(char *sended_data);
void fillstruct(char packet_type ,char *sended_data, int *packet_size);

int main(int argc, char *argv[])
{
	int sockfd;
	struct ifreq if_idx;
	struct ifreq if_mac;
	int tx_len = 0;
	char sendbuf[BUF_SIZ];
	struct ether_header *eh = (struct ether_header *) sendbuf;
	struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];
	
	/* Get interface name */
	/*if (argc > 1)
		strcpy(ifName, argv[1]);
	else
		strcpy(ifName, DEFAULT_IF);
	*/

	strcpy(ifName, DEFAULT_IF);

	/* Open RAW socket to send on */
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
	    perror("socket");
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
	    perror("SIOCGIFINDEX");
	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
	    perror("SIOCGIFHWADDR");

	/* Construct the Ethernet header */
	memset(sendbuf, 0, BUF_SIZ);
	/* Ethernet header */
	eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
	eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
	eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
	eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
	eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
	eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
	eh->ether_dhost[0] = MY_DEST_MAC0;
	eh->ether_dhost[1] = MY_DEST_MAC1;
	eh->ether_dhost[2] = MY_DEST_MAC2;
	eh->ether_dhost[3] = MY_DEST_MAC3;
	eh->ether_dhost[4] = MY_DEST_MAC4;
	eh->ether_dhost[5] = MY_DEST_MAC5;
	/* Ethertype field */
	eh->ether_type = htons(0x1234);
	tx_len += sizeof(struct ether_header);

	/* Packet data */
	//sendbuf[tx_len++] = 0x01;
	//sendbuf[tx_len++] = 0x68;
	//sendbuf[tx_len++] = 0x65;
	//sendbuf[tx_len++] = 0x6c;
	//sendbuf[tx_len++] = 0x6c;
	//sendbuf[tx_len++] = 0x6f;

	//sendbuf[tx_len] = 0x01; // type of packet
	
	//tx_len += fillstruct(&sendbuf[tx_len ]);
	
	char packet_type = 0x05;
	//printf("%d\n",packet_type);
	//char control=(char)*argv[1];
	//int temp=*argv[1];
	//packet_type=temp;
	//printf("%d\n",*argv[1]);
	printf("%d\n",packet_type);
	//strcpy(packet_type,(char) argv[1]);


	int tx_len_packet_size;

	fillstruct(packet_type, &sendbuf[tx_len], &tx_len_packet_size);
	tx_len += (int)tx_len_packet_size;

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;
	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;
	/* Destination MAC */
	socket_address.sll_addr[0] = MY_DEST_MAC0;
	socket_address.sll_addr[1] = MY_DEST_MAC1;
	socket_address.sll_addr[2] = MY_DEST_MAC2;
	socket_address.sll_addr[3] = MY_DEST_MAC3;
	socket_address.sll_addr[4] = MY_DEST_MAC4;
	socket_address.sll_addr[5] = MY_DEST_MAC5;

	/* Send packet */
	if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");

	//memset(&sendbuf[0],0,1024);
	return 0;
}



void fillstruct(char packet_type ,char *sended_data, int *packet_size)
{
	
	char Type_send =(char) packet_type;


	if(Type_send == QUERY_BROADCAST)
	{
		struct discovery_broadcast my_query_bcast;
		memset(&my_query_bcast, 0, sizeof(struct discovery_broadcast));
		//fill_query_bcast(&my_query_bcast);
		my_query_bcast.type = QUERY_BROADCAST;
	    snprintf(my_query_bcast.requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
	    snprintf(my_query_bcast.requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
	    memcpy(sended_data, &my_query_bcast,sizeof(struct discovery_broadcast));
	    *packet_size =(int) (sizeof(struct discovery_broadcast));
    }

    else if (Type_send == QUERY_UNICAST)
    {
    	struct discovery_unicast my_query_ucast;
    	memset(&my_query_ucast, 0, sizeof(struct discovery_unicast));
		my_query_ucast.type = QUERY_UNICAST;
	    snprintf(my_query_ucast.requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
	    snprintf(my_query_ucast.requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
	    snprintf(my_query_ucast.target_name, MAX_NAME_SIZE, "%s", TARGET_NAME);
	    snprintf(my_query_ucast.target_surname, MAX_NAME_SIZE, "%s", TARGET_SURNAME);
		memcpy(sended_data, &my_query_ucast,sizeof(struct discovery_unicast));
		*packet_size =(int) (sizeof(struct discovery_unicast));
	}
	else if (Type_send == HELLO_RESPONSE)
	{
		struct hello_response my_hello_response;
		memset(&my_hello_response,0,sizeof(struct hello_response));
		my_hello_response.type = HELLO_RESPONSE;
		snprintf(my_hello_response.responder_name, MAX_NAME_SIZE, "%s", MY_NAME);
		snprintf(my_hello_response.responder_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
		snprintf(my_hello_response.queryier_name, MAX_NAME_SIZE, "%s", TARGET_NAME);
		snprintf(my_hello_response.queryier_surname, MAX_NAME_SIZE, "%s", TARGET_SURNAME);
		memcpy(sended_data, &my_hello_response,sizeof(struct hello_response));
		*packet_size =(int) (sizeof(struct hello_response));
	}
	else if (Type_send == CHAT)
	{
		struct chat my_chat;
		memset(&my_chat,0,sizeof(struct chat));
		my_chat.type = CHAT;
		//snprintf(my_chat.length, 2, "%d", (int) LENGHT);
		//snprintf(my_chat.packet_id, 1, "%d", PACKET_ID);
		my_chat.length = htons(LENGHT);
		my_chat.packet_id = PACKET_ID;
		snprintf(my_chat.message, 100, "%s", MESSAGE);

		memcpy(sended_data, &my_chat, sizeof(struct chat));
		*packet_size =(int) (sizeof(struct chat));
	}
	else if (Type_send == CHAT_ACK)
	{
		struct chat_ACK my_chat_ACK;
		memset(&my_chat_ACK,0,sizeof(struct chat_ACK));
		my_chat_ACK.type = CHAT_ACK;
		my_chat_ACK.packet_id = PACKET_ID;
		memcpy(sended_data, &my_chat_ACK, sizeof(struct chat));
		*packet_size =(int) (sizeof(struct chat_ACK));
	}
	else if (Type_send == EXITING )
	{
		struct exiting my_exiting;
		memset(&my_exiting,0,sizeof(struct exiting));
		my_exiting.type = EXITING;
		snprintf(my_exiting.name,MAX_NAME_SIZE,"%s",MY_NAME);
		snprintf(my_exiting.surname,MAX_NAME_SIZE,"%s",MY_SURNAME);
		memcpy(sended_data, &my_exiting, sizeof(struct exiting));
		*packet_size =(int) (sizeof(struct exiting));
	}

}






// 		# additional fiil struct function #
/*int fillstruct(char *sended_data)
{
	char Type_send = sended_data[0];

	if(Type_send == QUERY_BROADCAST)
	{
		struct discovery_broadcast my_query_bcast;
		memset(&my_query_bcast, 0, sizeof(struct discovery_broadcast));
		//fill_query_bcast(&my_query_bcast);
		my_query_bcast.type = QUERY_BROADCAST;
	    snprintf(my_query_bcast.requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
	    snprintf(my_query_bcast.requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
	    memcpy(sended_data, &my_query_bcast,sizeof(struct discovery_broadcast));

	    return sizeof(struct discovery_broadcast);
    }

    else if (Type_send == QUERY_UNICAST)
    {
    	struct discovery_unicast my_query_ucast;
    	memset(&my_query_ucast, 0, sizeof(struct discovery_unicast));
		my_query_ucast.type = QUERY_UNICAST;
	    snprintf(my_query_ucast.requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
	    snprintf(my_query_ucast.requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
	    snprintf(my_query_ucast.target_name, MAX_NAME_SIZE, "%s", TARGET_NAME);
	    snprintf(my_query_ucast.target_surname, MAX_NAME_SIZE, "%s", TARGET_SURNAME);
		memcpy(sended_data, &my_query_ucast,sizeof(struct discovery_unicast));

		return sizeof(struct discovery_unicast);
    }
}*/

