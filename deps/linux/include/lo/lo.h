/*
 * Main liblo header file
 */

#ifndef LO_H
#define LO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lo/lo_types.h"
#include "lo/lo_osc_types.h"
#include "lo/lo_errors.h"
#include "lo/lo_lowlevel.h"
#include "lo/lo_serverthread.h"
#include "lo/lo_endian.h"

/* Macros for high-level API */
#define lo_send(targ, path, types, ...) \
    lo_send_internal(targ, __FILE__, __LINE__, path, types, __VA_ARGS__)

#define lo_send_from(targ, from, ts, path, types, ...) \
    lo_send_from_internal(targ, from, __FILE__, __LINE__, ts, path, types, __VA_ARGS__)

#define lo_send_timestamped(targ, ts, path, types, ...) \
    lo_send_timestamped_internal(targ, __FILE__, __LINE__, ts, path, types, __VA_ARGS__)

/* High-level API function declarations that are not in lo_lowlevel.h */
lo_address lo_address_new(const char *host, const char *port);
lo_address lo_address_new_from_url(const char *url);
lo_address lo_address_new_with_proto(int proto, const char *host, const char *port);
void lo_address_free(lo_address a);

int lo_address_errno(lo_address a);
const char *lo_address_errstr(lo_address a);

#ifdef __cplusplus
}
#endif

#endif /* LO_H */
