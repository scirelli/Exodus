#ifndef __HIERARCHICALSTORAGETREE_H__
#define __HIERARCHICALSTORAGETREE_H__
#define XML_STATIC
#define XML_UNICODE_WCHAR_T
#include <expat.h>
#include "HierarchicalStorageInterface/HierarchicalStorageInterface.pkg"
#include "HierarchicalStorageNode.h"
#include <vector>

class HierarchicalStorageTree :public IHierarchicalStorageTree
{
public:
	// Constructors
	HierarchicalStorageTree();
	~HierarchicalStorageTree();
	void Initialize();

	// Save/Load functions
	//##TODO## Take the storage mode into account when saving and loading
	virtual bool SaveTree(Stream::IStream& target);
	virtual bool LoadTree(Stream::IStream& source);

	// Storage mode functions
	virtual StorageMode GetStorageMode() const;
	virtual void SetStorageMode(StorageMode astorageMode);
	virtual bool GetSeparateBinaryDataEnabled() const;
	virtual void SetSeparateBinaryDataEnabled(bool state);

	// Error handling functions
	virtual Marshal::Ret<std::wstring> GetErrorString() const;

	// Node access functions
	virtual IHierarchicalStorageNode& GetRootNode() const;
	virtual Marshal::Ret<std::list<IHierarchicalStorageNode*>> GetBinaryDataNodeList();

private:
	// Save/Load functions
	bool SaveNode(IHierarchicalStorageNode& node, Stream::IStream& stream, const std::wstring& indentPrefix) const;
	static void XMLCALL LoadStartElement(void *userData, const XML_Char *aname, const XML_Char **aatts);
	static void XMLCALL LoadEndElement(void *userData, const XML_Char *aname);
	static void XMLCALL LoadData(void *userData, const XML_Char *s, int len);

	// Reserved character substitution functions
	bool IsCharacterReserved(wchar_t character) const;
	std::wstring GetNumericCharacterReference(wchar_t character) const;

private:
	StorageMode _storageMode;
	HierarchicalStorageNode* _root;
	IHierarchicalStorageNode* _currentNodeDuringLoad;
	mutable std::wstring _errorString;
	bool _allowSeparateBinaryData;
};

#endif
