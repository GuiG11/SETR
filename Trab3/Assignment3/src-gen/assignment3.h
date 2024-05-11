/** Generated by itemis CREATE code generator. */

#ifndef ASSIGNMENT3_H_
#define ASSIGNMENT3_H_

#ifdef __cplusplus
extern "C" { 
#endif

/*!
* Forward declaration for the Assignment3 state machine.
*/
typedef struct Assignment3 Assignment3;

/*!
* Forward declaration of the data structure for the Assignment3Internal interface scope.
*/
typedef struct Assignment3Internal Assignment3Internal;

/*!
* Forward declaration of the data structure for the Assignment3IfaceBut1 interface scope.
*/
typedef struct Assignment3IfaceBut1 Assignment3IfaceBut1;

/*!
* Forward declaration of the data structure for the Assignment3IfaceBut2 interface scope.
*/
typedef struct Assignment3IfaceBut2 Assignment3IfaceBut2;

/*!
* Forward declaration of the data structure for the Assignment3IfaceBut3 interface scope.
*/
typedef struct Assignment3IfaceBut3 Assignment3IfaceBut3;

/*!
* Forward declaration of the data structure for the Assignment3IfaceBut4 interface scope.
*/
typedef struct Assignment3IfaceBut4 Assignment3IfaceBut4;

/*!
* Forward declaration of the data structure for the Assignment3IfaceLed1 interface scope.
*/
typedef struct Assignment3IfaceLed1 Assignment3IfaceLed1;

/*!
* Forward declaration of the data structure for the Assignment3IfaceLed2 interface scope.
*/
typedef struct Assignment3IfaceLed2 Assignment3IfaceLed2;

/*!
* Forward declaration of the data structure for the Assignment3IfaceLed3 interface scope.
*/
typedef struct Assignment3IfaceLed3 Assignment3IfaceLed3;

/*!
* Forward declaration of the data structure for the Assignment3IfaceLed4 interface scope.
*/
typedef struct Assignment3IfaceLed4 Assignment3IfaceLed4;

#ifdef __cplusplus
}
#endif

#include "../src/sc_types.h"
#include <string.h>

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file
Header of the state machine 'assignment3'.
*/

#ifndef ASSIGNMENT3_EVENTQUEUE_BUFFERSIZE
#define ASSIGNMENT3_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef ASSIGNMENT3_IN_EVENTQUEUE_BUFFERSIZE
#define ASSIGNMENT3_IN_EVENTQUEUE_BUFFERSIZE ASSIGNMENT3_EVENTQUEUE_BUFFERSIZE
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define number of states in the state enum */
#define ASSIGNMENT3_STATE_COUNT 3

/*! Define dimension of the state configuration vector for orthogonal states. */
#define ASSIGNMENT3_MAX_ORTHOGONAL_STATES 1

/*! Define indices of states in the StateConfVector */
#define SCVI_ASSIGNMENT3_MAIN_REGION_IDLE 0
#define SCVI_ASSIGNMENT3_MAIN_REGION_DISPENSE 0
#define SCVI_ASSIGNMENT3_MAIN_REGION_RETURN_CREDIT 0


/* 
 * Enum of event names in the statechart.
 */
typedef enum  {
	Assignment3_invalid_event = SC_INVALID_EVENT_VALUE,
	Assignment3_but1_Insert,
	Assignment3_but2_Insert,
	Assignment3_but3_Browse,
	Assignment3_but4_Enter
} Assignment3EventID;

/*
 * Struct that represents a single event.
 */
typedef struct {
	Assignment3EventID name;
} assignment3_event;

/*
 * Queue that holds the raised events.
 */
typedef struct assignment3_eventqueue_s {
	assignment3_event *events;
	sc_integer capacity;
	sc_integer pop_index;
	sc_integer push_index;
	sc_integer size;
} assignment3_eventqueue;

/*! Enumeration of all states */ 
typedef enum
{
	Assignment3_last_state,
	Assignment3_main_region_Idle,
	Assignment3_main_region_Dispense,
	Assignment3_main_region_Return_Credit
} Assignment3States;


/*! Type declaration of the data structure for the Assignment3Internal interface scope. */
struct Assignment3Internal
{
	sc_integer Credit;
	sc_integer Product;
	sc_integer Price;
};



/*! Type declaration of the data structure for the Assignment3IfaceBut1 interface scope. */
struct Assignment3IfaceBut1
{
	sc_boolean Insert_raised;
};



/*! Type declaration of the data structure for the Assignment3IfaceBut2 interface scope. */
struct Assignment3IfaceBut2
{
	sc_boolean Insert_raised;
};



/*! Type declaration of the data structure for the Assignment3IfaceBut3 interface scope. */
struct Assignment3IfaceBut3
{
	sc_boolean Browse_raised;
};



/*! Type declaration of the data structure for the Assignment3IfaceBut4 interface scope. */
struct Assignment3IfaceBut4
{
	sc_boolean Enter_raised;
};



/*! Type declaration of the data structure for the Assignment3IfaceLed1 interface scope. */
struct Assignment3IfaceLed1
{
	sc_integer Power;
};



/*! Type declaration of the data structure for the Assignment3IfaceLed2 interface scope. */
struct Assignment3IfaceLed2
{
	sc_integer Power;
};



/*! Type declaration of the data structure for the Assignment3IfaceLed3 interface scope. */
struct Assignment3IfaceLed3
{
	sc_integer Power;
};



/*! Type declaration of the data structure for the Assignment3IfaceLed4 interface scope. */
struct Assignment3IfaceLed4
{
	sc_integer Power;
};






/*! 
 * Type declaration of the data structure for the Assignment3 state machine.
 * This data structure has to be allocated by the client code. 
 */
struct Assignment3
{
	Assignment3States stateConfVector[ASSIGNMENT3_MAX_ORTHOGONAL_STATES];
	Assignment3Internal internal;
	Assignment3IfaceBut1 ifaceBut1;
	Assignment3IfaceBut2 ifaceBut2;
	Assignment3IfaceBut3 ifaceBut3;
	Assignment3IfaceBut4 ifaceBut4;
	Assignment3IfaceLed1 ifaceLed1;
	Assignment3IfaceLed2 ifaceLed2;
	Assignment3IfaceLed3 ifaceLed3;
	Assignment3IfaceLed4 ifaceLed4;
	sc_boolean isExecuting;
	assignment3_eventqueue in_event_queue;
	assignment3_event in_buffer[ASSIGNMENT3_IN_EVENTQUEUE_BUFFERSIZE];
};



/*! Initializes the Assignment3 state machine data structures. Must be called before first usage.*/
extern void assignment3_init(Assignment3* handle);


/*! Activates the state machine. */
extern void assignment3_enter(Assignment3* handle);

/*! Deactivates the state machine. */
extern void assignment3_exit(Assignment3* handle);

/*! 
Can be used by the client code to trigger a run to completion step without raising an event.
*/
extern void assignment3_trigger_without_event(Assignment3* handle);



/*! Raises the in event 'Insert' that is defined in the interface scope 'but1'. */ 
extern void assignment3_but1_raise_insert(Assignment3* handle);
/*! Raises the in event 'Insert' that is defined in the interface scope 'but2'. */ 
extern void assignment3_but2_raise_insert(Assignment3* handle);
/*! Raises the in event 'Browse' that is defined in the interface scope 'but3'. */ 
extern void assignment3_but3_raise_browse(Assignment3* handle);
/*! Raises the in event 'Enter' that is defined in the interface scope 'but4'. */ 
extern void assignment3_but4_raise_enter(Assignment3* handle);
/*! Gets the value of the variable 'Power' that is defined in the interface scope 'led1'. */ 
extern sc_integer assignment3_led1_get_power(const Assignment3* handle);
/*! Sets the value of the variable 'Power' that is defined in the interface scope 'led1'. */ 
extern void assignment3_led1_set_power(Assignment3* handle, sc_integer value);
/*! Gets the value of the variable 'Power' that is defined in the interface scope 'led2'. */ 
extern sc_integer assignment3_led2_get_power(const Assignment3* handle);
/*! Sets the value of the variable 'Power' that is defined in the interface scope 'led2'. */ 
extern void assignment3_led2_set_power(Assignment3* handle, sc_integer value);
/*! Gets the value of the variable 'Power' that is defined in the interface scope 'led3'. */ 
extern sc_integer assignment3_led3_get_power(const Assignment3* handle);
/*! Sets the value of the variable 'Power' that is defined in the interface scope 'led3'. */ 
extern void assignment3_led3_set_power(Assignment3* handle, sc_integer value);
/*! Gets the value of the variable 'Power' that is defined in the interface scope 'led4'. */ 
extern sc_integer assignment3_led4_get_power(const Assignment3* handle);
/*! Sets the value of the variable 'Power' that is defined in the interface scope 'led4'. */ 
extern void assignment3_led4_set_power(Assignment3* handle, sc_integer value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean assignment3_is_active(const Assignment3* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean assignment3_is_final(const Assignment3* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean assignment3_is_state_active(const Assignment3* handle, Assignment3States state);


#ifdef __cplusplus
}
#endif 

#endif /* ASSIGNMENT3_H_ */
