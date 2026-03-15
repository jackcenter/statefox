#include <stdio.h>

#include "statefox.h"

enum { STATE_IDLE, STATE_RUNNING, STATE_ERROR };
enum { EVT_START, EVT_STOP, EVT_FAULT };

void handle_fault(sf_fsm_t* sm, const sf_event_t* evt) {
    printf("FAULT! Going to ERROR state\n");
}

sf_transition_t transitions[] = {
    {STATE_IDLE, EVT_START, STATE_RUNNING, NULL},
    {STATE_RUNNING, EVT_STOP, STATE_IDLE, NULL},
    {SF_ANY_STATE, EVT_FAULT, STATE_ERROR, handle_fault},
};

int main(void) {
    sf_fsm_t sm;
    sf_init(&sm, STATE_IDLE, transitions, sizeof(transitions) / sizeof(transitions[0]), NULL);

    sf_event_t evt = {.id = EVT_START, .data = NULL};
    sf_dispatch(&sm, &evt);
    printf("Current state: %d\n", sm.state);

    evt.id = EVT_FAULT;
    sf_dispatch(&sm, &evt);
    printf("Current state: %d\n", sm.state);

    return 0;
}
