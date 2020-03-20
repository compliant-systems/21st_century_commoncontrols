#pragma once

#include <assert.h>
#include <stdlib.h>

#define TASK_DIALOGUE_SAMPLER

/*
------------------------------------------------------------
*/
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef TASK_DIALOGUE_SAMPLER
    void task_dialog_simplex(_In_ HINSTANCE hInst);
    void task_dialog_complex(_In_ HINSTANCE hInst);
#endif // TASK_DIALOGUE_SAMPLER

    void unicode_mbox();

    /* obviously a cludge */
    inline void mbox(const char message[]) 
    {
        assert( message );
        MessageBoxA(NULL, message , (__argv ? __argv[0] : "__argv not ready" ), MB_OK);
    };

#ifdef __cplusplus
} // "C"
#endif // __cplusplus
