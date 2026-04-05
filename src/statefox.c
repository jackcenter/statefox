#include "statefox.h"

#include "sf_status.h"

sf_status_t sf_init(sf_state_t const initial_state, sf_transition_t const* transition_table,
                    size_t const transition_count, sf_fsm_t* fsm) {
  if (transition_table == NULL) {
    return (sf_status_t){.code = SF_INVALID_ARGUMENT, .message = "transition_table is null"};
  }

  if (fsm == NULL) {
    return (sf_status_t){.code = SF_INVALID_ARGUMENT, .message = "fsm is null"};
  }

  fsm->state            = initial_state;
  fsm->transition_table = transition_table;
  fsm->transition_count = transition_count;

  return (sf_status_t){.code = SF_OKAY, .message = NULL};
}

sf_status_t sf_dispatch(sf_event_t const* const event, sf_fsm_t* const fsm) {
  if (event == NULL) {
    return (sf_status_t){.code = SF_INVALID_ARGUMENT, .message = "event is null"};
  }

  if (fsm == NULL) {
    return (sf_status_t){.code = SF_INVALID_ARGUMENT, .message = "fsm is null"};
  }

  for (size_t i = 0; i < fsm->transition_count; ++i) {
    const sf_transition_t* transition = &fsm->transition_table[i];
    if ((transition->current_state == fsm->state) && (transition->event_id == event->id)) {
      if (transition->action != NULL) {
        transition->action(fsm, event);
      }

      fsm->state = transition->next_state;
      return (sf_status_t){.code = SF_OKAY, .message = NULL};
    }
  }

  return (sf_status_t){.code = SF_NOT_FOUND, .message = "transition not found"};
}
