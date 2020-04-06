/** Generated by YAKINDU Statechart Tools code generator. */


#include "yet_sc_tracer.h"
		
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static sc_string default_scope_name = "statechart";

static void trace(yet_sc_tracer* tracer, sc_machine_ptr machine, sc_trace_event event);
static void traceFeature(yet_sc_tracer* tracer, sc_machine_ptr machine, sc_trace_event event, sc_integer feature_id, const void * payload);
static void traceState(yet_sc_tracer* tracer, sc_machine_ptr machine, sc_trace_event event, sc_integer state_id);
static void traceTimeEvent(yet_sc_tracer* tracer, sc_machine_ptr machine, sc_trace_event event, sc_integer tevid);

static void sendMessage(yet_sc_tracer* tracer, sc_string key, sc_string value, sc_boolean meta);


void yet_init_sc_tracer(yet_sc_tracer *self, sc_machine_ptr machine, yet_handler actor)
{
	if (self != sc_null) {
		self->traceEventHandler.trace = (sc_trace_fp) trace;
		self->traceEventHandler.traceState = (sc_trace_state_fp) traceState;
		self->traceEventHandler.traceFeature = (sc_trace_feature_fp) traceFeature;
		self->traceEventHandler.traceTimeEvent = (sc_trace_time_event_fp) traceTimeEvent;

		yet_scope_init(&(self->scope), sc_null, default_scope_name, actor, self);

		self->machine = machine;
		self->skip_raised_in_event = 0;
		self->is_running = bool_false;
	}
}


static void trace(yet_sc_tracer* tracer, sc_machine_ptr machine, sc_trace_event event)
{
	switch(event) {
		case sc_trace_machine_enter:
			sendMessage(tracer, "Enter", "1", true); // TODO: why '1' ?!?
			tracer->is_running = true;
			break;
		case sc_trace_machine_exit:
			sendMessage(tracer, "Exit", "1", true); // TODO: why '1' ?!?
			tracer->is_running = false;
			break;
		case sc_trace_machine_run_cycle_start:
			sendMessage(tracer, "RunCycleStart", sc_null, true);
			break;
		case sc_trace_machine_run_cycle_end:
			sendMessage(tracer, "RunCycleEnd", sc_null, true);
			break;
		default:
			break;
	}

}

static void traceFeature(yet_sc_tracer* tracer, sc_machine_ptr handle, sc_trace_event event, sc_integer feature_id, const void * payload)
{
	char buf[30];
	switch(event) {
		case sc_trace_event_raised:
			// TODO: check if this is really required. If not we can omit the switch statement.
			if(tracer->skip_raised_in_event > 0) {
				tracer->skip_raised_in_event--;
				return;
			}
			sendMessage(tracer,
					tracer->traceinfoProvider.featureName(feature_id),
					tracer->traceinfoProvider.featureValue(feature_id, payload, buf), false);
			break;
		case sc_trace_variable_set:
			sendMessage(tracer,
					tracer->traceinfoProvider.featureName(feature_id),
					tracer->traceinfoProvider.featureValue(feature_id, payload, buf), false);
			break;
		default:
			break;
	}

}

static void traceState(yet_sc_tracer* tracer, sc_machine_ptr handle, sc_trace_event event, sc_integer state_id)
{
	switch(event) {
		case sc_trace_state_entered:
			sendMessage(tracer, "StateEntered", tracer->traceinfoProvider.stateName(state_id), true);
			break;
		case sc_trace_state_exited:
			sendMessage(tracer, "StateExited", tracer->traceinfoProvider.stateName(state_id), true);
			break;
		default:
			break;
	}
}

static void traceTimeEvent(yet_sc_tracer* tracer, sc_machine_ptr handle, sc_trace_event event, sc_integer tevid)
{
	char buf[21];

	switch(event) {
		case sc_trace_time_event_raised:
			sprintf(buf, "tev.%d.Expire", tevid); // TODO: substitute Expire by Raised
			sendMessage(tracer, buf, sc_null, true);
			break;
		case sc_trace_time_event_set:
			sprintf(buf, "tev.%d.Set", tevid);
			sendMessage(tracer, buf, sc_null, true);
			break;
		case sc_trace_time_event_unset:
			sprintf(buf, "tev.%d.Unset", tevid);
			sendMessage(tracer, buf, sc_null, true);
			break;
		default:
			break;
	}

}


/* TODO : remove is_running stuff and move this method to YET */
static void sendMessage(yet_sc_tracer* tracer, sc_string key, sc_string value, sc_boolean meta)
{
	char key_scoped[255]; // TODO: move buffer declaration
	struct yet_message msg;

	if(tracer->is_running) {
		msg.type = UPDATE;
		msg.timestamp = get_current_timestamp();
	} else {
		msg.type = INIT;
	}

	yet_scope_create_message(&(tracer->scope), key, key_scoped, meta);

	msg.key = key_scoped;
	msg.value = value;
	yet_scope_send(&(tracer->scope), &msg);
}		
		
		
