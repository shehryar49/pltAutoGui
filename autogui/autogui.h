#pragma once
#ifdef AUTOGUI_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif
#include "PltObject.h"
using namespace std;
extern "C"
{
	EXPORT void getMousePos(PltObject*, int, PltObject*);
	EXPORT void mouse_leftClick(PltObject*, int, PltObject*);
	EXPORT void mouse_rightClick(PltObject*, int, PltObject*);
	EXPORT void pressKey(PltObject*, int, PltObject*);
	EXPORT void typewrite(PltObject*, int, PltObject*);
	EXPORT void getKeyCodes(PltObject* args, int, PltObject*);
}