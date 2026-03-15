#ifndef STATEFOX_H
#define STATEFOX_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum { SF_ANY_STATE = UINT16_MAX, SF_ANY_EVENT = UINT16_MAX };

typedef struct sf_fsm sf_fsm_t; // FSM instance

typedef struct {
    uint16_t id;
    void*    data; // Arbitrary user payload
} sf_event_t;

typedef void (*sf_action_fn)(sf_fsm_t* sm, const sf_event_t* evt);

typedef struct {
    uint16_t     state;  // Current state
    uint16_t     event;  // Event ID
    uint16_t     next;   // Next state
    sf_action_fn action; // Optional callback
} sf_transition_t;

struct sf_fsm {
    uint16_t               state;
    const sf_transition_t* table;
    size_t                 count;
    void*                  context; // Optional user data
};

// Core FSM API
void sf_init(sf_fsm_t* sm, uint16_t initial_state, const sf_transition_t* table, size_t count,
             void* context);

void sf_dispatch(sf_fsm_t* sm, const sf_event_t* evt);

#endif // STATEFOX_H
