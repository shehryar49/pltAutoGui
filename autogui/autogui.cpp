#include "pch.h"
#include "autogui.h"

EXPORT void getMousePos(PltObject* args, int n, PltObject* rr)
{;
	if (n != 0)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "0 arguments needed! ");
		return;
	}
	POINT p;
	if (GetCursorPos(&p))
	{
		PltList* l = new PltList;//will be deallocated by interpreter's GC
		l->push_back(PltObjectFromInt(p.x));
		l->push_back(PltObjectFromInt(p.y));
		rr->type = 'j';
		rr->ptr = (void*)l;


	}
}
EXPORT void mouse_leftClick(PltObject* args, int n, PltObject* rr)
{
	if (n != 2)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "2 arguments needed! ");
		return;
	}
	if (args[0].type != 'i' || args[1].type != 'i')
	{
		*rr = Plt_Err(TYPE_ERROR, "Invalid type of arguments! ");
		return;
	}
	double fwidth = GetSystemMetrics(SM_CXSCREEN);
	double fheight = GetSystemMetrics(SM_CYSCREEN);
    double x = args[0].i * (65535.0f / fwidth);
	double y = args[1].i * (65535.0f / fheight);

	INPUT inputs[2] = {0};
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dx = x;
	inputs[0].mi.dy = y;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dx = x;
	inputs[1].mi.dy = y;
	inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(2, inputs, sizeof(INPUT));
	Sleep(10);
}
EXPORT void mouse_rightClick(PltObject* args, int n, PltObject* rr)
{
	if (n != 2)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "2 arguments needed! ");
		return;
	}
	if (n != 2)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "2 arguments needed! ");
		return;
	}
	if (args[0].type != 'i' || args[1].type != 'i')
	{
		*rr = Plt_Err(TYPE_ERROR, "Invalid type of arguments! ");
		return;
	}
	double fwidth = GetSystemMetrics(SM_CXSCREEN);
	double fheight = GetSystemMetrics(SM_CYSCREEN);
	double x = args[0].i * (65535.0f / fwidth);
	double y = args[1].i * (65535.0f / fheight);

	INPUT inputs[2] = { 0 };
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dx = x;
	inputs[0].mi.dy = y;
	inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dx = x;
	inputs[1].mi.dy = y;
	inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(2, inputs, sizeof(INPUT));
	Sleep(10);
}
EXPORT void pressKey(PltObject* args, int n, PltObject* rr)
{
	if (n != 1)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "0 arguments needed! ");
		return;
	}
	if (args[0].type != 'i')
	{
		*rr = Plt_Err(TYPE_ERROR, "Invalid type of arguments! ");
		return;
	}
	int key = args[0].i;
	INPUT inputs[2] = {0};
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wScan = 0;
	inputs[0].ki.time = 0;
	inputs[0].ki.dwExtraInfo = 0;
	inputs[0].ki.wVk = key;
	inputs[0].ki.dwFlags = 0;
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wScan = 0;
	inputs[1].ki.time = 0;
	inputs[1].ki.dwExtraInfo = 0;
	inputs[1].ki.wVk = key;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, inputs, sizeof(INPUT));
	Sleep(10);
}
EXPORT void getKeyCodes(PltObject* args, int n, PltObject* rr)
{
	Dictionary* d = new Dictionary;
	d->emplace(PltObjectFromString("ENTER"), PltObjectFromInt(VK_RETURN));
	d->emplace(PltObjectFromString("BACKSPACE"), PltObjectFromInt(VK_BACK));
	d->emplace(PltObjectFromString("LEFT"), PltObjectFromInt(VK_LEFT));
	d->emplace(PltObjectFromString("RIGHT"), PltObjectFromInt(VK_RIGHT));
	d->emplace(PltObjectFromString("UP"), PltObjectFromInt(VK_UP));
	d->emplace(PltObjectFromString("DOWN"), PltObjectFromInt(VK_DOWN));
	d->emplace(PltObjectFromString("SHIFT"), PltObjectFromInt(VK_SHIFT));
	d->emplace(PltObjectFromString("CAPSLOCK"), PltObjectFromInt(VK_CAPITAL));
	d->emplace(PltObjectFromString("CONTROL"), PltObjectFromInt(VK_CONTROL));
	d->emplace(PltObjectFromString("ESC"), PltObjectFromInt(VK_ESCAPE));
	d->emplace(PltObjectFromString("ALT"), PltObjectFromInt(VK_MENU));
	rr->type = 'a';
	rr->ptr = (void*)d;
}
EXPORT void typewrite(PltObject* args, int n, PltObject* rr)
{
	if (n != 1)
	{
		*rr = Plt_Err(ARGUMENT_ERROR, "0 arguments needed! ");
		return;
	}
	if (args[0].type != 's')
	{
		*rr = Plt_Err(TYPE_ERROR, "Invalid type of arguments! ");
		return;
	}
	string str = args[0].s;
	for (char key : str)
	{
		if (key == 32)
		{
			key = VK_SPACE;
		}
		else if (key >= 'A' && key <= 'z')
		{
			key = toupper(key);
		}
		else
		{
			*rr = Plt_Err(VALUE_ERROR, "error string should contain spaces and alphabets only!");
			return;
		}
		INPUT inputs[2] = { 0 };
		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wScan = 0;
		inputs[0].ki.time = 0;
		inputs[0].ki.dwExtraInfo = 0;
		inputs[0].ki.wVk = key;
		inputs[0].ki.dwFlags = 0;
		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wScan = 0;
		inputs[1].ki.time = 0;
		inputs[1].ki.dwExtraInfo = 0;
		inputs[1].ki.wVk = key;
		inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(2, inputs, sizeof(INPUT));
		Sleep(10);
	}
}
