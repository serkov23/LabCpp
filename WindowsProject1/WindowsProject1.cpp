// точка входа

#include "stdafx.h"
#include "KDeque.h"
#include "stream.h"
#include "resource.h"
#include "Avereger.h"
#include "MVC.h"
#include <fstream>
#include <vector>
#include <deque>
HWND _hdialog;


INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

template<class T>
INT_PTR parse_command(Controller<T>& a, Controller<T>& b, HWND hwnd, short control_id);

INT_PTR parse_msg(HWND hwnd, UINT msg, WPARAM wparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

template<class T>
INT_PTR parse_command(Controller<T>& a, Controller<T>& b, HWND hwnd, short control_id) {
	
	try {
		if (control_id & 1) {
			return a.parse_controll(hwnd, control_id, b,IDC_EDIT_A,IDC_LIST_A);
		}
		else {
			return b.parse_controll(hwnd, control_id - 1, a, IDC_EDIT_B, IDC_LIST_B);
		}
	}
	catch (std::exception& e) {
		MessageBoxA(hwnd, e.what(), "Error", MB_OK | MB_ICONERROR);
		a.clear();
		b.clear();
	}
	return TRUE;
}

INT_PTR parse_msg(HWND hwnd, UINT msg, WPARAM wparam) {
	static Controller<Person> a(KDeque<Person>(), View(hwnd, IDC_LIST_A)), b(KDeque<Person>(), View(hwnd, IDC_LIST_B));

	switch (msg)
	{
	case WM_INITDIALOG: {
		std::ifstream fin("data.txt");
		a.read(fin);
		b.read(fin);
		break;
	}
	case WM_COMMAND: {
		auto control_id = LOWORD(wparam);
		return parse_command(a, b, hwnd, control_id);
	}

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;

	default:
		//DefDlgProc(hwnd, msg, wparam, lparam);
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg)
	{
	case WM_INITDIALOG: case WM_COMMAND: case WM_CLOSE: case WM_DESTROY:
		return parse_msg(hwnd, msg, wparam);
	default:
		return FALSE;
	}
	return TRUE;
}