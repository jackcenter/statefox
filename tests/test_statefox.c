#include <assert.h>
#include <stdio.h>

#include "sf_status.h"
#include "statefox.h"

static size_t counter = 0;

static void increment_counter() {
  ++counter;
}

static void clear_counter() {
  counter = 0;
}

void test_fsm_simple() {
  typedef enum { STATE_IDLE, STATE_RUNNING, STATE_COUNT } State;
  typedef enum { EVENT_START, EVENT_STOP, EVENT_COUNT } Event;

  sf_transition_t const transition_table[] = {
      {STATE_IDLE, EVENT_START, STATE_RUNNING, increment_counter},
      {STATE_RUNNING, EVENT_STOP, STATE_IDLE, increment_counter},
  };
  size_t const transition_count = sizeof(transition_table) / sizeof(transition_table[0]);

  sf_fsm_t fsm;
  {
    sf_status_t const status = sf_init(STATE_IDLE, transition_table, transition_count, &fsm);
    assert(sf_status_is_okay(status));
    assert(fsm.state == STATE_IDLE);
  }

  clear_counter();

  sf_event_t event = {.id = EVENT_START, .data = NULL};
  {
    sf_status_t const status = sf_dispatch(&event, &fsm);
    assert(sf_status_is_okay(status));
    assert(fsm.state == STATE_RUNNING);
    assert(counter == 1);
  }
}

int main() {
  test_fsm_simple();
  printf("All tests passed!\n");
  return 0;
}
