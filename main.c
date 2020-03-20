
#define NOMINMAX
#define STRICT
#include <windows.h>
#include "common.h"
/*
------------------------------------------------------------
*/
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
  task_dialog_simplex(hInstance);
  task_dialog_complex(hInstance);
  unicode_mbox();
    return 0;
}