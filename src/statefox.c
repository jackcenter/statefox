#include "statefox.h"

// cppcheck-suppress unusedFunction
void sf_init(sf_fsm_t* sm, uint16_t initial_state, const sf_transition_t* table, size_t count,
             void* context) {
    sm->state   = initial_state;
    sm->table   = table;
    sm->count   = count;
    sm->context = context;
}

// cppcheck-suppress unusedFunction
void sf_dispatch(sf_fsm_t* sm, const sf_event_t* evt) {
    for (size_t i = 0; i < sm->count; i++) {
        const sf_transition_t* t = &sm->table[i];
        if ((t->state == sm->state || t->state == SF_ANY_STATE) &&
            (t->event == evt->id || t->event == SF_ANY_EVENT)) {
            if (t->action) t->action(sm, evt);
            sm->state = t->next;
            return;
        }
    }
}
