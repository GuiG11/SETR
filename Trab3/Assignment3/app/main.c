#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sc_types.h"
#include "assignment3.h"

assignment3_event ed;  		// Event Queue
assignment3_buffer buffer;
VM VMStateMachine;    		// The state machine structure variable


#define EVT_1CREDIT 'o'
#define EVT_2CREDIT 't'
#define EVT_BROWSE 	'b'
#define EVT_ENTER	's'
#define EVT_EXIT	'e'

// Thread prototypes
void *SSICode(void *arg);
void *UIOCode(void *arg);


int main(void)
{
	int err; // General return value variable

	pthread_t SSIThreadId, UIOThreadId; // Threads IDs
	void *threadResult; 				// Thread termination result

	// Init event queue
	assignment3_eventqueue_init(&ed, &buffer, 0);

	// Create the state machine interface thread
	err = pthread_create(&SSIThreadId, NULL, SSICode, NULL);
	if (err != 0)
	{
		perror("Error creating SM Thread");
		return -1;
	}

	// Create the UserIO emulation thread
	err = pthread_create(&UIOThreadId, NULL, UIOCode, NULL);
	if (err != 0)
	{
		perror("Error creating user IO emulation thread");
		return -1;
	}

	// Join both threads
	err = pthread_join(SSIThreadId, &threadResult);
	if (err != 0)
	{
		perror("Error joining SM thread");
		exit(EXIT_FAILURE);
	}

	err = pthread_join(UIOThreadId, &threadResult);
	if (err != 0)
	{
		perror("Error joining user IO emulation thread");
		exit(EXIT_FAILURE);
	}
}

void *UIOCode(void *arg)
{
	int opt; // User choice

	do
	{
		// Show menu
		printf("\nVending Machine UI emulation\n");
		printf("O - Insert one coin\n");
		printf("T - Insert two coins\n");
		printf("B - Browse products\n");
		printf("S - Select option\n");
		printf("E - Exit\n");

		do
		{
			opt = getchar();
		} while (opt < ' ');

		// Process the user input generating the matching event
		switch (opt)
		{
			case 'O':
			case 'o':
				assignment3_add_event_to_queue(&ed, EVT_1CREDIT);
				break;

			case 'T':
			case 't':
				assignment3_add_event_to_queue(&ed, EVT_2CREDIT);
				break;

			case 'B':
			case 'b':
				assignment3_add_event_to_queue(&ed, EVT_BROWSE);
				break;

			case 'S':
			case 's':
				assignment3_add_event_to_queue(&ed, EVT_ENTER);
				break;

			case 'E':
			case 'e':
				assignment3_add_event_to_queue(&ed, EVT_EXIT);
				break;
		}

	} while (opt != 'e' && opt != 'E');

	pthread_exit("Terminating UI emulation thread\n");
}


void *SSICode(void *arg)
{
	int err;				 // Return value variable
	int credit, product;

	// Init the state machine
	assignement3_init(&VMStateMachine);

	// Enters the state machine
	assignment3_enter(&VMStateMachine);

	do
	{
		// Read the next event
		err = assignment3_get_next_event(&VMStateMachine);

		// Process the event
		if (err != bool_false)
		{
			switch (err)
			{
				case EVT_1CREDIT:
					credit = assignment3_but1_raise_insert(&VMStateMachine);
					printf("\t Credit: %d\n", assignment3_internal_set_credit(&VMStateMachine, credit));
					break;

				case EVT_2CREDIT:
					credit = assignment3_but2_raise_insert(&VMStateMachine);
					credit += 2;
					printf("\t Credit: %d\n", credit);
					break;

				case EVT_BROWSE:
					product = assignment3_but3_raise_browse(&VMStateMachine);
					printf("\t Product: %d\n", product);
					printf("\t Led1: %d\n", assignment3_led1_get_power(&VMStateMachine));
					printf("\t Led2: %d\n", assignment3_led2_get_power(&VMStateMacgine));
					break;

				case EVT_ENTER:
					assignment3_but4_raise_enter(&VMStateMachine);
					printf("\t Credit: %d\n", credit);
					printf("\t Product: %d\n", product);
					printf("\t Led3: %d\n", assignment3_led3_get_power(&VMStateMachine));
					printf("\t Led4: %d\n", assignment3_led4_get_power(&VMStateMachine));
					break;

				case EVT_EXIT:
					printf("Exit\n");
					break;
			}
		}
	} while (err != EVT_EXIT);

	assignment3_exit(&VMStateMachine);
	pthread_exit("Terminating State Machine thread\n");
}
