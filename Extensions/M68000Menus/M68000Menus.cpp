#include "M68000Menus.h"
#include "DebugMenuHandler.h"
#include "M68000/IM68000.h"

//----------------------------------------------------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------------------------------------------------
M68000Menus::M68000Menus(const std::wstring& implementationName, const std::wstring& instanceName, unsigned int moduleID)
:Extension(implementationName, instanceName, moduleID)
{ }

//----------------------------------------------------------------------------------------------------------------------
M68000Menus::~M68000Menus()
{
	// Delete all menu handlers
	for (std::map<IDevice*, DebugMenuHandler*>::const_iterator i = _debugMenuHandlers.begin(); i != _debugMenuHandlers.end(); ++i)
	{
		i->second->ClearMenuItems();
		delete i->second;
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Window functions
//----------------------------------------------------------------------------------------------------------------------
bool M68000Menus::RegisterDeviceMenuHandler(IDevice* targetDevice)
{
	// Attempt to cast the supplied device to the correct type
	IM68000* targetDeviceAsIM68000 = dynamic_cast<IM68000*>(targetDevice);
	if (targetDeviceAsIM68000 == 0)
	{
		return false;
	}

	// Create a new menu handler for the target device
	DebugMenuHandler* menuHandler = new DebugMenuHandler(*this, *targetDevice, *targetDeviceAsIM68000);
	menuHandler->LoadMenuItems();
	_debugMenuHandlers[targetDevice] = menuHandler;
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
void M68000Menus::UnregisterDeviceMenuHandler(IDevice* targetDevice)
{
	DebugMenuHandler* menuHandler = _debugMenuHandlers[targetDevice];
	menuHandler->ClearMenuItems();
	delete menuHandler;
	_debugMenuHandlers.erase(targetDevice);
}

//----------------------------------------------------------------------------------------------------------------------
void M68000Menus::AddDeviceMenuItems(DeviceMenu deviceMenu, IMenuSegment& menuSegment, IDevice* targetDevice)
{
	if (deviceMenu == IExtension::DeviceMenu::Debug)
	{
		_debugMenuHandlers[targetDevice]->AddMenuItems(menuSegment);
	}
}

//----------------------------------------------------------------------------------------------------------------------
bool M68000Menus::RestoreDeviceViewState(const Marshal::In<std::wstring>& viewGroupName, const Marshal::In<std::wstring>& viewName, IHierarchicalStorageNode& viewState, IViewPresenter** restoredViewPresenter, IDevice* targetDevice)
{
	return _debugMenuHandlers[targetDevice]->RestoreMenuViewOpen(viewGroupName, viewName, viewState, restoredViewPresenter);
}

//----------------------------------------------------------------------------------------------------------------------
bool M68000Menus::OpenDeviceView(const Marshal::In<std::wstring>& viewGroupName, const Marshal::In<std::wstring>& viewName, IDevice* targetDevice)
{
	return _debugMenuHandlers[targetDevice]->OpenView(viewGroupName, viewName);
}
