/**
 * @file sf_status.h
 * @brief Status and error reporting types for Statefox.
 *
 * Defines sf_status_t, the return type used by all Statefox API functions,
 * along with sf_code_t for machine-readable error codes and sf_status_is_okay()
 * for convenient success checks.
 *
 * This header has no dependencies on the FSM itself and may be used
 * independently in other projects.
 *
 * @author Jack Center
 * @date April 5th, 2026
 */

#ifndef SF_STATUS_H
#define SF_STATUS_H

#include <stdbool.h>

/**
 * @brief Return codes for Statefox API functions.
 *
 * @var SF_OKAY
 *   The operation completed successfully.
 * @var SF_INVALID_ARGUMENT
 *   A required argument was NULL or otherwise invalid.
 * @var SF_NOT_FOUND
 *   No transition matched the current state and event.
 */
typedef enum {
  SF_OKAY,
  SF_INVALID_ARGUMENT,
  SF_NOT_FOUND,
} sf_code_t;

/**
 * @struct sf_status_t
 * @brief Return value for all Statefox API functions.
 *
 * On success, `code` is `SF_OKAY` and `message` is NULL.
 * On failure, `code` indicates the error category and `message`
 * contains a human-readable description, including relevant state
 * and event IDs where applicable.
 *
 * @var sf_status_t::code
 *   Machine-readable result code. Check this programmatically.
 * @var sf_status_t::message
 *   Human-readable description of the error. Do not parse this string.
 *   Points to a string literal and does not need to be freed.
 */
typedef struct {
  sf_code_t   code;
  const char* message;
} sf_status_t;

/**
 * @brief Returns true if  `status` represents success.
 *
 * Equivalent to checking `status.code` == `SF_OKAY`.
 *
 * @param[in] status The status to check.
 * @return true if the operation succeeded, false otherwise.
 */
bool sf_status_is_okay(sf_status_t const status);

#endif  // SF_STATUS_H
