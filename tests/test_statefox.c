#include <assert.h>
#include <stdio.h>

#include "statefox.h"

static int fault_called = 0;

void handle_fault(sf_fsm_t* sm, const sf_event_t* evt) {
    fault_called = 1;
}

void test_fsm_simple() {
    enum { STATE_IDLE, STATE_RUNNING, STATE_ERROR };
    enum { EVT_START, EVT_STOP, EVT_FAULT };

    sf_transition_t transitions[] = {
        {STATE_IDLE, EVT_START, STATE_RUNNING, NULL},
        {STATE_RUNNING, EVT_STOP, STATE_IDLE, NULL},
        {SF_ANY_STATE, EVT_FAULT, STATE_ERROR, handle_fault},
    };

    sf_fsm_t sm;
    sf_init(&sm, STATE_IDLE, transitions, 3, NULL);

    sf_event_t evt = {.id = EVT_START, .data = NULL};
    sf_dispatch(&sm, &evt);
    assert(sm.state == STATE_RUNNING);

    evt.id = EVT_FAULT;
    sf_dispatch(&sm, &evt);
    assert(sm.state == STATE_ERROR);
    assert(fault_called);
}

int main() {
    test_fsm_simple();
    printf("All tests passed!\n");
    return 0;
}
