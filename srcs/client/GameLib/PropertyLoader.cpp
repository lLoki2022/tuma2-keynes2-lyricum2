#include "StdAfx.h"
#include "PropertyLoader.h"
#include "PropertyManager.h"
#include "Property.h"

bool CPropertyLoader::OnFolder(const char* c_szFilter, const char* c_szPathName, const char* c_szFileName)
{
	std::string stPathName = "";
	stPathName += c_szPathName;
	stPathName += c_szFileName;

	CPropertyLoader PropertyLoader;
//	PropertyLoader.SetPropertyManager(m_pPropertyManager);
	PropertyLoader.Create(c_szFilter, stPathName.c_str());
	return true;
}

bool CPropertyLoader::OnFile(const char* c_szPathName, const char* c_szFileName)
{
	RegisterFile(c_szPathName, c_szFileName);
	return true;
}

DWORD CPropertyLoader::RegisterFile(const char* c_szPathName, const char* c_szFileName)
{
	std::string strFileName = "";
	strFileName += c_szPathName;
	strFileName += c_szFileName;

	std::string stExt;
	GetFileExtension(strFileName.c_str(), strFileName.length(), &stExt);

	stl_lowers(stExt);
	stl_lowers(strFileName);

	StringPath(strFileName);

//	CProperty* pProperty;
//
//	if (m_pPropertyManager->Register(strFileName.c_str(), &pProperty)) {
//		return pProperty->GetCRC();
//	}
	CProperty* pProperty;
	if (CPropertyManager::Instance().Register(strFileName.c_str(), &pProperty))
		return pProperty->GetCRC();

	return 0;
}

//void CPropertyLoader::SetPropertyManager(CPropertyManager* pPropertyManager)
//{
//	m_pPropertyManager = pPropertyManager;
//}

//CPropertyLoader::CPropertyLoader()
//{
//	m_pPropertyManager = NULL;
//}

CPropertyLoader::~CPropertyLoader() = default;
