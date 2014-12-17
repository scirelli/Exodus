#ifndef __REGISTERSVIEW_H__
#define __REGISTERSVIEW_H__
#include "WindowsSupport/WindowsSupport.pkg"
#include "ExodusDeviceInterface/ExodusDeviceInterface.pkg"
#include "RegistersViewPresenter.h"
#include "M68000/IM68000.h"

class RegistersView :public ViewBase
{
public:
	//Constructors
	RegistersView(IUIManager& auiManager, RegistersViewPresenter& apresenter, IM68000& amodel);
	~RegistersView();

protected:
	//Member window procedure
	virtual INT_PTR WndProcDialog(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	//Event handlers
	INT_PTR msgWM_INITDIALOG(HWND hwnd, WPARAM wParam, LPARAM lParam);
	INT_PTR msgWM_DESTROY(HWND hwnd, WPARAM wParam, LPARAM lParam);
	INT_PTR msgWM_TIMER(HWND hwnd, WPARAM wParam, LPARAM lParam);
	INT_PTR msgWM_COMMAND(HWND hwnd, WPARAM wParam, LPARAM lParam);
	INT_PTR msgWM_CTLCOLOREDIT(HWND hwnd, WPARAM wParam, LPARAM lParam);

	//Changed register functions
	bool RegisterContentsChanged(int controlID);

private:
	RegistersViewPresenter& presenter;
	IM68000& model;
	bool initializedDialog;
	std::wstring previousText;
	unsigned int currentControlFocus;
	COLORREF changedColor;
	COLORREF backgroundColor;
	HBRUSH backgroundBrush;
	unsigned int systemPausedToggleCounterCached;
};

#endif