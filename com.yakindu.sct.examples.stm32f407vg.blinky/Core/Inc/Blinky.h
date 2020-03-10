/** Generated by YAKINDU Statechart Tools code generator. */

#ifndef BLINKY_H_
#define BLINKY_H_

#include <main.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f407xx.h>
#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'blinky'.
*/

#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define number of states in the state enum */

#define BLINKY_STATE_COUNT 2

/*! Define dimension of the state configuration vector for orthogonal states. */
#define BLINKY_MAX_ORTHOGONAL_STATES 1

/*! Define maximum number of time events that can be active at once */
#define BLINKY_MAX_PARALLEL_TIME_EVENTS 1

/*! Define indices of states in the StateConfVector */
#define SCVI_BLINKY_MAIN_REGION_LEDS_OFF 0
#define SCVI_BLINKY_MAIN_REGION_LEDS_ON 0



/*! Enumeration of all states */ 
typedef enum
{
	Blinky_last_state,
	Blinky_main_region_LEDs_off,
	Blinky_main_region_LEDs_on
} BlinkyStates;



/*! Type definition of the data structure for the BlinkyIface interface scope. */
typedef struct
{
	int8_t main;
} BlinkyIface;



/*! Type definition of the data structure for the BlinkyTimeEvents interface scope. */
typedef struct
{
	sc_boolean blinky_main_region_LEDs_off_tev0_raised;
	sc_boolean blinky_main_region_LEDs_on_tev0_raised;
} BlinkyTimeEvents;




/*! 
 * Type definition of the data structure for the Blinky state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	BlinkyStates stateConfVector[BLINKY_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	BlinkyIface iface;
	BlinkyTimeEvents timeEvents;
} Blinky;



/*! Initializes the Blinky state machine data structures. Must be called before first usage.*/
extern void blinky_init(Blinky* handle);

/*! Activates the state machine */
extern void blinky_enter(Blinky* handle);

/*! Deactivates the state machine */
extern void blinky_exit(Blinky* handle);

/*! Performs a 'run to completion' step. */
extern void blinky_runCycle(Blinky* handle);

/*! Raises a time event. */
extern void blinky_raiseTimeEvent(Blinky* handle, sc_eventid evid);

/*! Gets the value of the variable 'main' that is defined in the default interface scope. */ 
extern int8_t blinkyIface_get_main(const Blinky* handle);
/*! Sets the value of the variable 'main' that is defined in the default interface scope. */ 
extern void blinkyIface_set_main(Blinky* handle, int8_t value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean blinky_isActive(const Blinky* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean blinky_isFinal(const Blinky* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean blinky_isStateActive(const Blinky* handle, BlinkyStates state);


#ifdef __cplusplus
}
#endif 

#endif /* BLINKY_H_ */
