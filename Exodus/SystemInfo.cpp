#include "SystemInfo.h"

//----------------------------------------------------------------------------------------
//Interface version functions
//----------------------------------------------------------------------------------------
unsigned int SystemInfo::GetISystemInfoVersion() const
{
	return ThisISystemInfoVersion();
}

//----------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------
SystemInfo::AllocatorPointer SystemInfo::GetAllocator() const
{
	return Allocator;
}

//----------------------------------------------------------------------------------------
SystemInfo::DestructorPointer SystemInfo::GetDestructor() const
{
	return Destructor;
}

//----------------------------------------------------------------------------------------
unsigned int SystemInfo::GetSystemVersionNo() const
{
	return versionNo;
}

//----------------------------------------------------------------------------------------
Marshal::Ret<std::wstring> SystemInfo::GetSystemCopyright() const
{
	return copyright;
}

//----------------------------------------------------------------------------------------
Marshal::Ret<std::wstring> SystemInfo::GetSystemComments() const
{
	return comments;
}

//----------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------
void SystemInfo::SetSystemSettings(AllocatorPointer aAllocator, DestructorPointer aDestructor, unsigned int asystemVersionNo, const Marshal::In<std::wstring>& asystemCopyright, const Marshal::In<std::wstring>& asystemComments)
{
	SetSystemAllocators(aAllocator, aDestructor);
	SetSystemVersionNo(asystemVersionNo);
	SetSystemCopyright(asystemCopyright);
	SetSystemComments(asystemComments);
}

//----------------------------------------------------------------------------------------
void SystemInfo::SetSystemAllocators(AllocatorPointer aAllocator, DestructorPointer aDestructor)
{
	Allocator = aAllocator;
	Destructor = aDestructor;
}

//----------------------------------------------------------------------------------------
void SystemInfo::SetSystemVersionNo(unsigned int asystemVersionNo)
{
	versionNo = asystemVersionNo;
}

//----------------------------------------------------------------------------------------
void SystemInfo::SetSystemCopyright(const Marshal::In<std::wstring>& asystemCopyright)
{
	copyright = asystemCopyright;
}

//----------------------------------------------------------------------------------------
void SystemInfo::SetSystemComments(const Marshal::In<std::wstring>& asystemComments)
{
	comments = asystemComments;
}
