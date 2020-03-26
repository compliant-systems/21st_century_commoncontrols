
#define NOMINMAX
#define STRICT
#include <windows.h>

#include "common.h"

#ifdef TASK_DIALOGUE_SAMPLER

#ifdef UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

/*
------------------------------------------------------------
This actually shows proper glyphs on WIN19 up to date desktop
*/
void utf8_mbox() {
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
	config.pszMainInstruction = L"Change the Password\nSecond line of text\nAnd the third line too";
	config.pszContent = L"Remember your changed the password.\nBut really do remember.";
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);
	switch (nButtonPressed)
	{
	case IDOK:
		dbj_mbox(L"the user pressed button 0 (change password)");
		break; 
	case IDCANCEL:
		dbj_mbox(L"user canceled the dialog");
		break; 
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
	LPCWSTR szTitle = dbj_app_path() , szHeader = L"Header text", szCheckboxText = L"Check Box Text",
		szExtraInfo =
		L"This update was released on " DBJ_WIDE(__DATE__) L" " \
		L"\n" \
		L"<a href=\"https://dbj.org/\">Full details about this update</a>";
	TASKDIALOG_BUTTON aCustomButtons[] = { { 1000, L"One Custom Button" }, { 1001, L"Two Custom Buttons" } };

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
	tdc.lpCallbackData = (LONG_PTR)NULL;

	hr = TaskDialogIndirect(&tdc, &nClickedBtn, NULL, &bCheckboxChecked);
}

#endif // TASK_DIALOGUE_SAMPLER