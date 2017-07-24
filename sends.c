#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "packets.h"

#define MY_NAME "durmus"
#define MY_SURNAME "orcan"

#define TARGET_NAME "devin"
#define TARGET_SURNAME "mungan"

void fillstruct(char *sended_data)
{
	char Type_send = sended_data[15];

	if(Type_send == QUERY_BROADCAST)
	{
		struct discovery_broadcast my_query_bcast;
		//my_query_bcast = (struct discovery_broadcast*)sended_data;
		memset(&my_query_bcast, 0, sizeof(struct discovery_broadcast));

		fill_query_bcast(&my_query_bcast);


		//my_query_bcast->type = QUERY_BROADCAST;
	    //snprintf(my_query_bcast->requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
	    //snprintf(my_query_bcast->requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
	    //memcpy(*sended_data, *my_query_bcast, sizeof(struct discovery_broadcast));
	    //memset(&sended_data, (char)&my_query_bcast, sizeof(struct discovery_broadcast));
	    return;
	}


}

void fill_query_bcast(struct discovery_broadcast *q)
{
    q->type = QUERY_BROADCAST;
    snprintf(q->requester_name, MAX_NAME_SIZE, "%s", MY_NAME);
    snprintf(q->requester_surname, MAX_NAME_SIZE, "%s", MY_SURNAME);
}