// ParseIP.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ParseIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 唯一的应用程序对象

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}
	
	return nRetCode;
}


//导出的类
CParseIP::CParseIP()
{
	char szIPDatPath[MAX_PATH] = {0};
	//GetCurrentDirectory(MAX_PATH,szIPDatPath);
	HMODULE hModule = ::GetModuleHandle(NULL);
	GetModuleFileName(hModule,szIPDatPath,MAX_PATH);
	CString str(szIPDatPath);
	int n = str.ReverseFind(_T('\\'));
	CString strDatPath = str.Left(n);
	strDatPath = strDatPath + "\\QQWry.Dat";
	m_pReadQQWryDat = new CReadQQWryDat(strDatPath);
};

CParseIP::~CParseIP()
{
	if (m_pReadQQWryDat)
	{
		delete m_pReadQQWryDat;
		m_pReadQQWryDat = NULL;
	}
}

//获取本地主机名称
void CParseIP::GetLoaclhostName(char* pszHostName)
{
	 CString strHostName = m_pReadQQWryDat->GetLoaclHostName();
	 strcpy(pszHostName,strHostName.GetBuffer(0));
}

//返回本机IP地址 如果有多个 如果有多个。就用回车换行分割开来
void CParseIP::GetLoaclhostIP(char* pszHostIP)
{
	CString strIP = m_pReadQQWryDat->GetLoaclhostIP();
	strcpy(pszHostIP,strIP.GetBuffer(0));
}


/************************************************************************/
/* 字符串拆分函数                                                        */
/************************************************************************/
#include <vector>
using namespace std;
inline static void SplitChar(const char* content, const char* token,vector<CString>& vect)    
{    
	if(content == NULL)    
		return;    
	int len = strlen(content);    
	if(len <= 0)    
		return;    
	char* pBuf =(char*)malloc(len+1);    
	strcpy(pBuf , content);    
	char* str = strtok(pBuf , token);    
	while(str != NULL)    
	{    
		vect.push_back(str);    
		str = strtok(NULL,token);    
	}    
	free(pBuf);  
}
//返回本地主机IP对应的地址  
void CParseIP::GetLocalIPInfo(char* pszLoaclIPAddr)
{
	memset(pszLoaclIPAddr,0,strlen(pszLoaclIPAddr));
	CString strHostAddr ,strHostIpInfo;
	char szHostIP[MAX_PATH] = {0};
	GetLoaclhostIP(szHostIP);
	vector<CString> Vct_IP;
	SplitChar(szHostIP,"\n",Vct_IP);
	for (UINT i=0 ;i<Vct_IP.size();i++)
	{
		m_pReadQQWryDat->QueryIp2Addr(Vct_IP.at(i),strHostAddr);
		strHostIpInfo.Format("本机IP地址%d---%s--%s  || ",i+1,Vct_IP.at(i),strHostAddr);
		strcat(pszLoaclIPAddr,strHostIpInfo);
	}
	
}

void CParseIP::QueryIP2Addr(char* pszIP,char* pszAddr)
{
	CString strHostAddr;
	memset(pszAddr,0,strlen(pszAddr));
	m_pReadQQWryDat->QueryIp2Addr(pszIP,strHostAddr);
	strcat(pszAddr,strHostAddr);
}

//返回本地主机名称
extern "C" _declspec(dllexport) CString GetLoaclhostName(void)
{	
	CString strLocalHostName; 
	return strLocalHostName;
}

//返回本机IP地址 如果有多个 则以空白字符隔开
extern "C" _declspec(dllexport) CString GetLoaclhostIP(void)
{
	
	return NULL;
	//cReadQQWryDat.GetLoaclhostIP();	
}

//返回本地主机IP对应的地址
extern "C" _declspec(dllexport) CString GetLocalIPInfo(CString& strLocalIP)
{
	return NULL;
}

//返回指定IP对应的地址
extern "C" _declspec(dllexport) CString QueryIPInfo(CString& strIP)
{
	return NULL;
}

//获取纯真IP数据库的版本
extern "C" _declspec(dllexport) CString QueryDatVer()
{
	return NULL;
}
//获取IP数据库的记录条数
extern "C" _declspec(dllexport) int    QueryRecordCount()
{
	return NULL;
}

//更新IP数据库
extern "C" _declspec(dllexport) BOOL   UpdateIPDat()
{
	return FALSE;
}