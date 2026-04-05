/**
 * @file statefox.h
 * @brief Statefox — a lightweight finite state machine (FSM) library for C.
 * @author Jack Center
 * @date April 5th, 2026
 *
 * Usage:
 * 1. Define your states and events as enums.
 * 2. Build a transition table as an array of sf_transition_t.
 * 3. Initialize an sf_fsm_t with sf_init().
 * 4. Drive the machine by calling sf_dispatch() with events.
 */

#ifndef STATEFOX_H
#define STATEFOX_H

#include <stddef.h>
#include <stdint.h>

#include "sf_status.h"

typedef uint16_t sf_state_t;
typedef uint16_t sf_event_id_t;

/**
 * @struct sf_fsm_t
 * @brief Opaque handle to a Statefox FSM instance.
 *
 * Callers should not access fields directly. Use sf_init() and sf_dispatch()
 * to interact with the machine.
 */
typedef struct sf_fsm sf_fsm_t;  // forward declaration

/**
 * @struct sf_event_t
 * @brief An event dispatched to the FSM to trigger a transition.
 *
 * @var sf_event_t::id
 *   Identifies which event occurred. Matched against the transition table.
 * @var sf_event_t::data
 *   Optional payload passed through to the transition action. May be NULL.
 */
typedef struct {
  sf_event_id_t id;
  void*         data;
} sf_event_t;

/**
 * @brief Callback invoked when a transition is taken.
 *
 * @param fsm   The FSM to triggered the transition.
 * @param event The event that caused the transition.
 */
typedef void (*sf_action_fn)(sf_fsm_t* fsm, const sf_event_t* event);

/**
 * @struct sf_transition_t
 * @brief A single row in the FSM transition table.
 *
 * Describes a transition from `current_state` to `next_state` when `event_id` is dispatched,
 * optionally invoking `action`.
 *
 * @var sf_transition_t::current_state
 *   The state this transition applies to.
 * @var sf_transition_t::event_id
 *   The event that triggers this transition.
 * @var sf_transition_t::next_state
 *   The state the machine moves to after the transition.
 * @var sf_transition_t::action
 *   Called when the transition is taken. May be NULL for no-op transitions.
 */
typedef struct {
  sf_state_t    current_state;
  sf_event_id_t event_id;
  sf_state_t    next_state;
  sf_action_fn  action;
} sf_transition_t;

struct sf_fsm {
  sf_state_t             state;
  sf_transition_t const* transition_table;
  size_t                 transition_count;
};

/**
 * @brief Initialize an FSM.
 *
 * Populates `fsm` with the given initial state and transition table. The transition table is not
 * copied — it must remain valid for the lifetime of the FSM.
 *
 * @param[in] initial_state     The state the machine starts in.
 * @param[in] transition_table  Array of transitions defining the machine's behavior.
 * @param[in] transition_count  Number of entries in `transition_table`.
 * @param[out] fsm              Output parameter. Must point to valid storage.
 *
 * @return `SF_OKAY` on success.
 * @return `SF_INVALID_ARGUMENT` if `transition_table` or `fsm` is NULL.
 */
sf_status_t sf_init(sf_state_t const initial_state, sf_transition_t const* transition_table,
                    size_t const transition_count, sf_fsm_t* fsm);

/**
 * @brief Dispatch an event to the FSM.
 *
 * Searches the transition table for an entry matching the current state and event ID. If found,
 * invokes the associated action (if any) and advances to the next state. If no matching transition
 * exists, the event is silently ignored and the machine remains in its current state.
 *
 * @param[in] event The event to process.
 * @param[in,out] fsm  The FSM to dispatch to.
 *
 * @return `SF_OKAY` on success.
 * @return `SF_INVALID_ARGUMENT` if `event` or `fsm` is NULL.
 * @return `SF_NOT_FOUND` if no transition matches the current state and event ID.
 */
sf_status_t sf_dispatch(sf_event_t const* const event, sf_fsm_t* const fsm);

#endif  // STATEFOX_H
