#include "sample.h"
#include <interactor_data_pool.h>
#include <interactor_message.h>
#include <interactor_native.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool done = false;

interactor_native_t* sample_interactor_initialize()
{
    interactor_native_t* sample_interactor = malloc(sizeof(interactor_native_t));
    if (!sample_interactor)
    {
        return NULL;
    }
    int result = interactor_native_initialize_default(sample_interactor, 0);
    if (result < 0)
    {
        return NULL;
    }
    return sample_interactor;
}

void sample_interactor_destroy(interactor_native_t* interactor)
{
    interactor_native_destroy(interactor);
}

void sample_call_dart(interactor_message_t* message)
{
    printf("hello: %s\n", (char*)message->input);
    strcpy(message->output, "hello: I am C");
    done = true;
}

bool sample_check_dart(interactor_native_t* interactor)
{
    interactor_native_process_timeout(interactor);
    return done;
}