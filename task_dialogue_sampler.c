
#define NOMINMAX
#define STRICT
#include <windows.h>

#include "common.h"

#ifdef TASK_DIALOGUE_SAMPLER

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

/*
------------------------------------------------------------
Tom Honnerman sample from his proposal to WG14 
to finalize char8_t support
*/
 void unicode_mbox() {
    const char* caption =
        u8"\U0001F631";  // U+1F631 FACE SCREAMING IN FEAR
    const char* message =
        u8"\U0001F648"   // U+1F648 SEE-NO-EVIL MONKEY
        u8"\U0001F649"   // U+1F649 HEAR-NO-EVIL MONKEY
        u8"\U0001F64A";  // U+1F64A SPEAK-NO-EVIL MONKEY
    MessageBoxA(NULL, message, caption, MB_OK);
}

/*
------------------------------------------------------------
https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-taskdialog
*/


 void task_dialog_simplex(_In_ HINSTANCE hInst)
{
    int nButtonPressed = 0;
    TASKDIALOGCONFIG config = { 0 };
    const TASKDIALOG_BUTTON buttons[] = {
                                            { IDOK, L"Change password" }
    };
    config.cbSize = sizeof(config);
    config.hInstance = hInst;
    config.dwCommonButtons = TDCBF_CANCEL_BUTTON;
    config.pszMainIcon = TD_WARNING_ICON;
    config.pszMainInstruction = L"Change Password";
    config.pszContent = L"Remember your changed password.";
    config.pButtons = buttons;
    config.cButtons = ARRAYSIZE(buttons);

    TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);
    switch (nButtonPressed)
    {
    case IDOK:
        break; // the user pressed button 0 (change password).
    case IDCANCEL:
        break; // user canceled the dialog
    default:
        break; // should never happen
    }
}
/*
------------------------------------------------------------
*/

static HRESULT CALLBACK TDCallback(
    HWND hwnd, UINT uNotification, WPARAM wParam,
    LPARAM lParam, LONG_PTR dwRefData)
{
    switch (uNotification)
    {
    case TDN_HYPERLINK_CLICKED:
        ShellExecute(hwnd, L"open", (LPCWSTR)lParam,
            NULL, NULL, SW_SHOW);
        break;
    }

    return S_OK;
}

 void task_dialog_complex(_In_ HINSTANCE hInst)
{
    HRESULT hr;
    TASKDIALOGCONFIG tdc = { sizeof(TASKDIALOGCONFIG) };
    int nClickedBtn;
    BOOL bCheckboxChecked;
    LPCWSTR szTitle = L"...", szHeader = L"...", szCheckboxText = L"...",
        szExtraInfo =
        L"This update was released on March 12, 2020 " \
        L"\n" \
        L"<a href=\"http://www.example.com/\">Full details about this update</a>";
    TASKDIALOG_BUTTON aCustomButtons[] = { { 1000, L"..." }, { 1001, L"..." } };

    tdc.hwndParent = NULL; // m_hWnd;
    tdc.dwFlags = TDF_USE_COMMAND_LINKS | TDF_ENABLE_HYPERLINKS;
    tdc.pButtons = aCustomButtons;
    tdc.cButtons = _countof(aCustomButtons);
    tdc.pszWindowTitle = szTitle;
    tdc.pszMainIcon = TD_INFORMATION_ICON;
    tdc.pszMainInstruction = szHeader;
    tdc.pszExpandedInformation = szExtraInfo;
    tdc.pszVerificationText = szCheckboxText;
    tdc.pfCallback = TDCallback;
    // tdc.lpCallbackData = (LONG_PTR)this;

    hr = TaskDialogIndirect(&tdc, &nClickedBtn, NULL, &bCheckboxChecked);
}

#endif // TASK_DIALOGUE_SAMPLER