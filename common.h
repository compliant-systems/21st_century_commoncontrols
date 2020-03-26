#pragma once

#include <assert.h>
#include <crtdbg.h>
#include <stdlib.h>

#define TASK_DIALOGUE_SAMPLER

#define DBJ_WIDE2(x) L##x
#define DBJ_WIDE(x) DBJ_WIDE2(x)

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

	inline static const wchar_t * const dbj_app_path() 
	{
		// requires app start from wWinMain() 
		_ASSERTE(__wargv );
		return __wargv[0];
	}

	void utf8_mbox();

	inline void dbj_mbox(const wchar_t* message) {
		_ASSERTE(__wargv && message);
		const wchar_t* const caption = dbj_app_path();
		MessageBoxW(NULL, message, caption, MB_OK);
	}

#ifdef __cplusplus
} // "C"
#endif // __cplusplus
