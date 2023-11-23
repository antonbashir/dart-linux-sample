#ifndef SAMPLE_H
#define SAMPLE_H

#include <stdbool.h>
#if defined(__cplusplus)
extern "C"
{
#endif

    typedef struct interactor_native interactor_native_t;
    typedef struct interactor_message interactor_message_t;

    interactor_native_t* sample_interactor_initialize();
    void sample_interactor_destroy(interactor_native_t* interactor);
    void sample_call_dart(interactor_message_t* message);
    bool sample_check_dart(interactor_native_t* interactor);

#if defined(__cplusplus)
}
#endif

#endif