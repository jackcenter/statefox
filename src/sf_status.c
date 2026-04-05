#include "sf_status.h"

bool sf_status_is_okay(sf_status_t const status) {
  return status.code == SF_OKAY;
}
