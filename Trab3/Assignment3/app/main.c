#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "../src-gen/assignment3.h"

#define EVT_1CREDIT 'o'
#define EVT_2CREDIT 't'
#define EVT_BROWSE  'b'
#define EVT_ENTER   's'
#define EVT_EXIT    'e'

// Thread prototypes
void *userIOCode(void *arg);

int main(void)
{
    pthread_t userIOThreadId; // Thread ID for user IO emulation
    void *threadResult;       // Thread termination result

    // Initialize the state machine
    Assignment3 vendingMachine;
    assignment3_init(&vendingMachine);

    // Enter the state machine
    assignment3_enter(&vendingMachine);

    // Create the UserIO emulation thread
    if (pthread_create(&userIOThreadId, NULL, userIOCode, (void *)&vendingMachine) != 0)
    {
        perror("Error creating user IO emulation thread");
        return -1;
    }

    // Join the user IO emulation thread
    if (pthread_join(userIOThreadId, &threadResult) != 0)
    {
        perror("Error joining user IO emulation thread");
        return -1;
    }

    return 0;
}

void *userIOCode(void *arg)
{
    Assignment3 *vendingMachine = (Assignment3 *)arg;
    char opt; // User choice

    do
    {
        // Show menu
        printf("\nVending Machine UI emulation\n");
        printf("O - Insert one coin\n");
        printf("T - Insert two coins\n");
        printf("B - Browse products\n");
        printf("S - Select option\n");
        printf("E - Exit\n");

        // Read user input
        scanf(" %c", &opt);

        // Process the user input generating the matching event
        switch (opt)
        {
            case EVT_1CREDIT:
                assignment3_but1_raise_insert(vendingMachine);
                printf("Inserted 1 credit\n");
                break;

            case EVT_2CREDIT:
                assignment3_but2_raise_insert(vendingMachine);
                printf("Inserted 2 credits\n");
                break;

            case EVT_BROWSE:
                assignment3_but3_raise_browse(vendingMachine);
                printf("Browsing products...\n");
                break;

            case EVT_ENTER:
                assignment3_but4_raise_enter(vendingMachine);
                printf("Selected product.\n");
                break;

            case EVT_EXIT:
                printf("Exiting user IO emulation thread\n");
                break;

            default:
                printf("Invalid option\n");
                break;
        }

        // Print current credit and product information
        printf("Current credit: %d\n", vendingMachine->internal.Credit);
		printf("Selected product: %d\n", vendingMachine->internal.Product);
		printf("Price of selected product: %d\n", vendingMachine->internal.Price);

    } while (opt != EVT_EXIT);

    // Exit the state machine
    assignment3_exit(vendingMachine);

    // Terminate the thread
    pthread_exit(NULL);
}
