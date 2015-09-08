/*#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
*/

#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include <ach.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>

//#include "/home/pi/CRITR/ach-2.0.0/include/ach.h"



typedef struct
{
	int motor_id;
	int motor_pos;
} state_data;

void send_state_data(state_data state_data_struct,ach_channel_t channel)
{
	/* Fill in my_msg with useful data */
	enum ach_status r = ach_put( &channel, &state_data_struct, sizeof(state_data_struct) );
	if( ACH_OK != r ) 
	{
		printf("There was an error writing to the channel");
	}
}

state_data receive_state_data(ach_channel_t channel)
{
	
	/* Get the message */
	size_t frame_size = 60;
	state_data state_data_received;
	enum ach_status r = ach_get( &channel, &state_data_received, sizeof(state_data_received), &frame_size, NULL,ACH_O_WAIT | ACH_O_LAST);
	if( ACH_TIMEOUT == r ) 
	{
	  printf("There was an error writing to the channel");
	}
	return state_data_received;
}

//main
int main(int argc, char *argv[])
{
	//open client send channel	
	ach_channel_t csend;
	char sserver[10] = "sserver";
	char sclient[10] = "sclient";
	enum ach_status r = ach_open( &csend, sclient, NULL );
	if( ACH_OK != r ) 
	{  
	  printf("There was an error writing to the channel");
	}
	//open server send channel
	ach_channel_t ssend;
	r = ach_open( &ssend, sserver, NULL );
	if( ACH_OK != r ) 
	{	
	  printf("There was an error writing to the channel");
	}
	state_data desired_state;
	while(1)
	{
		desired_state = receive_state_data(csend);
		desired_state.motor_id =desired_state.motor_id+1;
		desired_state.motor_pos = desired_state.motor_pos+1;	
		send_state_data(desired_state,ssend);
		printf("motor_id = %d",desired_state.motor_id);
	}
	return 1;
} 
