/* C99 fallback for static_assert; the SDK otherwise requires C11.
 * SPDX-License-Identifier: BSD-3-Clause */
#ifndef _PICO_C99_STATIC_ASSERT_H
#define _PICO_C99_STATIC_ASSERT_H

#ifndef __ASSEMBLER__
#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L))
#define PICO_C99_SA_CAT_(a, b) a ## b
#define PICO_C99_SA_CAT(a, b) PICO_C99_SA_CAT_(a, b)
#define static_assert(cond, msg) typedef char PICO_C99_SA_CAT(pico_c99_static_assert_, __COUNTER__)[((cond) ? 1 : -1)] __attribute__((unused))
#endif
#endif

#endif
