/** Generated by YAKINDU Statechart Tools code generator. */

#include "../Inc/Blinky.h"
#include "../Inc/sc_types.h"
#include "../Inc/BlinkyRequired.h"

/*! \file Implementation of the state machine 'blinky'
*/

#define SC_UNUSED(P) (void)(P)
/* prototypes of all internal functions */
static void enact_main_region_LEDs_off(Blinky* handle);
static void enact_main_region_LEDs_on(Blinky* handle);
static void exact_main_region_LEDs_off(Blinky* handle);
static void exact_main_region_LEDs_on(Blinky* handle);
static void enseq_main_region_LEDs_off_default(Blinky* handle);
static void enseq_main_region_LEDs_on_default(Blinky* handle);
static void enseq_main_region_default(Blinky* handle);
static void exseq_main_region_LEDs_off(Blinky* handle);
static void exseq_main_region_LEDs_on(Blinky* handle);
static void exseq_main_region(Blinky* handle);
static void react_main_region__entry_Default(Blinky* handle);
static sc_boolean react(Blinky* handle);
static sc_boolean main_region_LEDs_off_react(Blinky* handle, const sc_boolean try_transition);
static sc_boolean main_region_LEDs_on_react(Blinky* handle, const sc_boolean try_transition);
static void clearInEvents(Blinky* handle);
static void clearOutEvents(Blinky* handle);



void blinky_init(Blinky* handle)
{
	sc_integer i;
	
	for (i = 0; i < BLINKY_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Blinky_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;
	
	clearInEvents(handle);
	clearOutEvents(handle);
	
	/* Default init sequence for statechart blinky */
	handle->iface.main = SCT_MAIN;
}

void blinky_enter(Blinky* handle)
{
	/* Default enter sequence for statechart blinky */
	enseq_main_region_default(handle);
}

void blinky_runCycle(Blinky* handle)
{
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < BLINKY_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Blinky_main_region_LEDs_off:
		{
			main_region_LEDs_off_react(handle, bool_true);
			break;
		}
		case Blinky_main_region_LEDs_on:
		{
			main_region_LEDs_on_react(handle, bool_true);
			break;
		}
		default:
			break;
		}
	}
	clearInEvents(handle);
}

void blinky_exit(Blinky* handle)
{
	/* Default exit sequence for statechart blinky */
	exseq_main_region(handle);
}

sc_boolean blinky_isActive(const Blinky* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < BLINKY_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Blinky_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean blinky_isFinal(const Blinky* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

void blinky_raiseTimeEvent(Blinky* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + (unsigned)sizeof(BlinkyTimeEvents))
	{
		*(sc_boolean*)evid = bool_true;
		
		blinky_runCycle(handle);
	}
}

sc_boolean blinky_isStateActive(const Blinky* handle, BlinkyStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Blinky_main_region_LEDs_off :
			result = (sc_boolean) (handle->stateConfVector[SCVI_BLINKY_MAIN_REGION_LEDS_OFF] == Blinky_main_region_LEDs_off
			);
			break;
		case Blinky_main_region_LEDs_on :
			result = (sc_boolean) (handle->stateConfVector[SCVI_BLINKY_MAIN_REGION_LEDS_ON] == Blinky_main_region_LEDs_on
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Blinky* handle)
{
	handle->timeEvents.blinky_main_region_LEDs_off_tev0_raised = bool_false;
	handle->timeEvents.blinky_main_region_LEDs_on_tev0_raised = bool_false;
}

static void clearOutEvents(Blinky* handle)
{
	SC_UNUSED(handle);
}



int8_t blinkyIface_get_main(const Blinky* handle)
{
	return handle->iface.main;
}
void blinkyIface_set_main(Blinky* handle, int8_t value)
{
	handle->iface.main = value;
}

/* implementations of all internal functions */

/* Entry action for state 'LEDs off'. */
static void enact_main_region_LEDs_off(Blinky* handle)
{
	/* Entry action for state 'LEDs off'. */
	blinky_setTimer(handle, (sc_eventid) &(handle->timeEvents.blinky_main_region_LEDs_off_tev0_raised) , (1 * 1000), bool_false);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

/* Entry action for state 'LEDs on'. */
static void enact_main_region_LEDs_on(Blinky* handle)
{
	/* Entry action for state 'LEDs on'. */
	blinky_setTimer(handle, (sc_eventid) &(handle->timeEvents.blinky_main_region_LEDs_on_tev0_raised) , (1 * 1000), bool_false);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
}

/* Exit action for state 'LEDs off'. */
static void exact_main_region_LEDs_off(Blinky* handle)
{
	/* Exit action for state 'LEDs off'. */
	blinky_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.blinky_main_region_LEDs_off_tev0_raised) );		
	SC_UNUSED(handle);
}

/* Exit action for state 'LEDs on'. */
static void exact_main_region_LEDs_on(Blinky* handle)
{
	/* Exit action for state 'LEDs on'. */
	blinky_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.blinky_main_region_LEDs_on_tev0_raised) );		
	SC_UNUSED(handle);
}

/* 'default' enter sequence for state LEDs off */
static void enseq_main_region_LEDs_off_default(Blinky* handle)
{
	/* 'default' enter sequence for state LEDs off */
	enact_main_region_LEDs_off(handle);
	handle->stateConfVector[0] = Blinky_main_region_LEDs_off;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state LEDs on */
static void enseq_main_region_LEDs_on_default(Blinky* handle)
{
	/* 'default' enter sequence for state LEDs on */
	enact_main_region_LEDs_on(handle);
	handle->stateConfVector[0] = Blinky_main_region_LEDs_on;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Blinky* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* Default exit sequence for state LEDs off */
static void exseq_main_region_LEDs_off(Blinky* handle)
{
	/* Default exit sequence for state LEDs off */
	handle->stateConfVector[0] = Blinky_last_state;
	handle->stateConfVectorPosition = 0;
	exact_main_region_LEDs_off(handle);
}

/* Default exit sequence for state LEDs on */
static void exseq_main_region_LEDs_on(Blinky* handle)
{
	/* Default exit sequence for state LEDs on */
	handle->stateConfVector[0] = Blinky_last_state;
	handle->stateConfVectorPosition = 0;
	exact_main_region_LEDs_on(handle);
}

/* Default exit sequence for region main region */
static void exseq_main_region(Blinky* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of blinky.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Blinky_main_region_LEDs_off :
		{
			exseq_main_region_LEDs_off(handle);
			break;
		}
		case Blinky_main_region_LEDs_on :
		{
			exseq_main_region_LEDs_on(handle);
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Blinky* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_LEDs_off_default(handle);
}

static sc_boolean react(Blinky* handle) {
	/* State machine reactions. */
	return bool_false;
	SC_UNUSED(handle);
}

static sc_boolean main_region_LEDs_off_react(Blinky* handle, const sc_boolean try_transition) {
	/* The reactions of state LEDs off. */
	sc_boolean did_transition = try_transition;
	if (try_transition == bool_true)
	{ 
		if ((react(handle)) == (bool_false))
		{ 
			if (handle->timeEvents.blinky_main_region_LEDs_off_tev0_raised == bool_true)
			{ 
				exseq_main_region_LEDs_off(handle);
				enseq_main_region_LEDs_on_default(handle);
			}  else
			{
				did_transition = bool_false;
			}
		} 
	} 
	return did_transition;
}

static sc_boolean main_region_LEDs_on_react(Blinky* handle, const sc_boolean try_transition) {
	/* The reactions of state LEDs on. */
	sc_boolean did_transition = try_transition;
	if (try_transition == bool_true)
	{ 
		if ((react(handle)) == (bool_false))
		{ 
			if (handle->timeEvents.blinky_main_region_LEDs_on_tev0_raised == bool_true)
			{ 
				exseq_main_region_LEDs_on(handle);
				enseq_main_region_LEDs_off_default(handle);
			}  else
			{
				did_transition = bool_false;
			}
		} 
	} 
	return did_transition;
}


