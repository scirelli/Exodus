#include "SettingsMenuHandler.h"
#include "InputMappingViewPresenter.h"
#include "InputMappingDetailsViewPresenter.h"
#include "EmbeddedROMViewPresenter.h"

//----------------------------------------------------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------------------------------------------------
SettingsMenuHandler::SettingsMenuHandler(ExodusSystemMenus& owner, ISystemGUIInterface& model)
:MenuHandlerBase(L"SystemSettingsMenu", owner.GetViewManager()), _owner(owner), _model(model)
{ }

//----------------------------------------------------------------------------------------------------------------------
// Management functions
//----------------------------------------------------------------------------------------------------------------------
void SettingsMenuHandler::GetMenuItems(std::list<MenuItemDefinition>& menuItems) const
{
	menuItems.push_back(MenuItemDefinition(MENUITEM_INPUTMAPPING, L"InputMapping", InputMappingViewPresenter::GetUnqualifiedViewTitle(), true));
	menuItems.push_back(MenuItemDefinition(MENUITEM_INPUTMAPPINGDETAILS, L"InputMappingDetails", InputMappingDetailsViewPresenter::GetUnqualifiedViewTitle(), true, false, true));
	menuItems.push_back(MenuItemDefinition(MENUITEM_EMBEDDEDROM, L"EmbeddedROMControl", EmbeddedROMViewPresenter::GetUnqualifiedViewTitle(), true));
}

//----------------------------------------------------------------------------------------------------------------------
IViewPresenter* SettingsMenuHandler::CreateViewForItem(int menuItemID, const std::wstring& viewName)
{
	switch (menuItemID)
	{
	case MENUITEM_INPUTMAPPING:
		return new InputMappingViewPresenter(GetMenuHandlerName(), viewName, MENUITEM_INPUTMAPPING, _owner, _model);
	case MENUITEM_EMBEDDEDROM:
		return new EmbeddedROMViewPresenter(GetMenuHandlerName(), viewName, MENUITEM_EMBEDDEDROM, _owner, _model);
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
void SettingsMenuHandler::DeleteViewForItem(int menuItemID, IViewPresenter* viewPresenter)
{
	delete viewPresenter;
}

//----------------------------------------------------------------------------------------------------------------------
// Window functions
//----------------------------------------------------------------------------------------------------------------------
void SettingsMenuHandler::OpenInputMappingDetailsView(IDevice* targetDevice)
{
	std::set<IViewPresenter*> viewPresenters = GetOpenViewPresenters(MENUITEM_INPUTMAPPINGDETAILS);
	if (!viewPresenters.empty())
	{
		IViewPresenter* viewPresenter = *viewPresenters.begin();
		InputMappingDetailsViewPresenter* inputMappingDetailsViewPresenter = dynamic_cast<InputMappingDetailsViewPresenter*>(viewPresenter);
		if (inputMappingDetailsViewPresenter != 0)
		{
			inputMappingDetailsViewPresenter->SetTargetDevice(targetDevice);
		}
	}
	else
	{
		IViewPresenter* viewPresenter = new InputMappingDetailsViewPresenter(GetMenuHandlerName(), GetMenuItemName(MENUITEM_INPUTMAPPINGDETAILS), MENUITEM_INPUTMAPPINGDETAILS, _owner, _model, targetDevice);
		if (!AddCreatedView(MENUITEM_INPUTMAPPINGDETAILS, viewPresenter))
		{
			delete viewPresenter;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void SettingsMenuHandler::CloseInputMappingDetailsView()
{
	std::set<IViewPresenter*> viewPresenters = GetOpenViewPresenters(MENUITEM_INPUTMAPPINGDETAILS);
	if (!viewPresenters.empty())
	{
		IViewPresenter* viewPresenter = *viewPresenters.begin();
		viewPresenter->CloseView();
	}
}
