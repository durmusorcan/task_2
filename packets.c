#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "packets.h"

void tostruct(char *add)
{
	char Type = (char)add[0];

	if(Type == QUERY_BROADCAST)
	{
		struct discovery_broadcast *my_dbp;
		my_dbp = (struct discovery_broadcast*)add;
		//q = (struct query_bcast*) bcast;


		//my_dbp->type=(char)QUERY_BROADCAST;
		//snprint(my_dbp->requester_name,10,"%s",add+sizeof(my_dbp->type));
		//snprint(my_dbp->requester_surname,10,"%s",add+sizeof(my_dbp->type)+sizeof(my_dbp->requester_name));
		
		fprintf(stdout, "* decoding broadcast query *\n");
	    fprintf(stdout, "my_dbp->type: %d\n", my_dbp->type);
		fprintf(stdout, "my_dbp->requester_name: %s\n", my_dbp->requester_name);
	    fprintf(stdout, "my_dbp->requester_surname: %s\n", my_dbp->requester_surname);
	}

	else if(Type == QUERY_UNICAST)
	{
		struct discovery_unicast *my_dup;
		my_dup = (struct discovery_unicast*)add;

		fprintf(stdout, "* decoding unicast query *\n");
	    fprintf(stdout, "my_dup->type: %d\n", my_dup->type);
		fprintf(stdout, "my_dup->requester_name: %s\n", my_dup->requester_name);
	    fprintf(stdout, "my_dup->requester_surname: %s\n", my_dup->requester_surname);
	    fprintf(stdout, "my_dup->target_name: %s\n", my_dup->target_name);
	    fprintf(stdout, "my_dup->target_surname: %s\n", my_dup->target_surname);

	}
	else if(Type == HELLO_RESPONSE)
	{
		struct hello_response *my_hrp;
		my_hrp = (struct hello_response*)add;

		fprintf(stdout, "* hello response *\n");
	    fprintf(stdout, "my_hrp->type: %d\n", my_hrp->type);
		fprintf(stdout, "my_hrp->responder_name: %s\n", my_hrp->responder_name);
	    fprintf(stdout, "my_hrp->responder_surname: %s\n", my_hrp->responder_surname);
	    fprintf(stdout, "my_hrp->queryier_name: %s\n", my_hrp->queryier_name);
	    fprintf(stdout, "my_hrp->queryier_surname: %s\n", my_hrp->queryier_surname);

	}

	else if(Type == CHAT)
	{
		struct chat *my_cp;
		my_cp = (struct chat*)add;


		fprintf(stdout, "* chat *\n");
	    fprintf(stdout, "my_cp->type: %d\n", my_cp->type);
	    fprintf(stdout, "my_cp->lenght: %d\n",htons(my_cp->length);
	    fprintf(stdout, "my_cp->packet_id: %d\n", my_cp->packet_id);
	    fprintf(stdout, "my_cp->message: %s\n", my_cp->message);
	}

	else if(Type == CHAT_ACK)
	{
		struct chat_ACK *my_cap;
		my_cap = (struct chat_ACK*)add;

		fprintf(stdout, "* chat_ACK *\n");
		fprintf(stdout, "my_cap->type: %d\n", my_cap->type);
		fprintf(stdout, "my_cap->packet_id: %d\n", my_cap->packet_id);

	}

	else if(Type == EXITING)
	{
		struct exiting *my_ep;
		my_ep = (struct exiting*)add;
		fprintf(stdout, "* exiting *\n");
	    fprintf(stdout, "my_ep->type: %d\n", my_ep->type);
		fprintf(stdout, "my_ep->name: %s\n", my_ep->name);
	    fprintf(stdout, "my_ep->surname: %s\n", my_ep->surname);
	}

}
