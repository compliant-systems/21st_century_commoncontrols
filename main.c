
#define NOMINMAX
#define STRICT
#include <windows.h>
#include "common.h"
/*
------------------------------------------------------------
NOTE: must use wWinMain or wmain for proper UNICODE support
__wargv might be NULL if app is not started 
from wWinMain or wmain
*/
int CALLBACK wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
  task_dialog_simplex(hInstance);
  task_dialog_complex(hInstance);
//  utf8_mbox();
    return 0;
}
