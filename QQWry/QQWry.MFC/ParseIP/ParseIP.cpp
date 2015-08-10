// ParseIP.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ParseIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}
	
	return nRetCode;
}


//��������
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

//��ȡ������������
void CParseIP::GetLoaclhostName(char* pszHostName)
{
	 CString strHostName = m_pReadQQWryDat->GetLoaclHostName();
	 strcpy(pszHostName,strHostName.GetBuffer(0));
}

//���ر���IP��ַ ����ж�� ����ж�������ûس����зָ��
void CParseIP::GetLoaclhostIP(char* pszHostIP)
{
	CString strIP = m_pReadQQWryDat->GetLoaclhostIP();
	strcpy(pszHostIP,strIP.GetBuffer(0));
}


/************************************************************************/
/* �ַ�����ֺ���                                                        */
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
//���ر�������IP��Ӧ�ĵ�ַ  
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
		strHostIpInfo.Format("����IP��ַ%d---%s--%s  || ",i+1,Vct_IP.at(i),strHostAddr);
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

//���ر�����������
extern "C" _declspec(dllexport) CString GetLoaclhostName(void)
{	
	CString strLocalHostName; 
	return strLocalHostName;
}

//���ر���IP��ַ ����ж�� ���Կհ��ַ�����
extern "C" _declspec(dllexport) CString GetLoaclhostIP(void)
{
	
	return NULL;
	//cReadQQWryDat.GetLoaclhostIP();	
}

//���ر�������IP��Ӧ�ĵ�ַ
extern "C" _declspec(dllexport) CString GetLocalIPInfo(CString& strLocalIP)
{
	return NULL;
}

//����ָ��IP��Ӧ�ĵ�ַ
extern "C" _declspec(dllexport) CString QueryIPInfo(CString& strIP)
{
	return NULL;
}

//��ȡ����IP���ݿ�İ汾
extern "C" _declspec(dllexport) CString QueryDatVer()
{
	return NULL;
}
//��ȡIP���ݿ�ļ�¼����
extern "C" _declspec(dllexport) int    QueryRecordCount()
{
	return NULL;
}

//����IP���ݿ�
extern "C" _declspec(dllexport) BOOL   UpdateIPDat()
{
	return FALSE;
}