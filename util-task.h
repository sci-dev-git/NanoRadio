#ifndef UTIL_TASK_H_
#define UTIL_TASK_H_

#include "portable.h"

typedef void (*pfn_util_task_callback)(void *opaque);
typedef uintptr_t util_semaphore_t;
typedef uintptr_t util_mutex_t;

typedef enum{
  CORE_PROTO_STACK,
  CORE_CODEC,
  CORE_STREAM,
  CORE_CTRL
} util_coreid_t;

extern int NC_P(util_create_task)(pfn_util_task_callback callback, const char *name, int stack_size, util_coreid_t coreid, void *opaque);
extern void NC_P(util_task_exit)(void);
extern void NC_P(util_task_yield)(void);
extern void NC_P(util_task_sleep)(int ms);
extern int NC_P(util_task_get_free_heap)(void);

extern util_semaphore_t util_create_semaphore(int value);
extern int util_semaphore_take(util_semaphore_t sem);
extern int util_semaphore_give(util_semaphore_t sem);
extern void util_destroy_semaphore(util_semaphore_t sem);

extern util_mutex_t util_create_mutex(void);
extern void util_mutex_take(util_mutex_t mutex);
extern void util_mutex_give(util_mutex_t mutex);
extern void util_mutex_destroy(util_mutex_t mutex);

#endif
