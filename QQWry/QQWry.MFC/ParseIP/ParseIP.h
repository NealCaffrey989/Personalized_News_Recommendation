// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PARSEIP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PARSEIP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef PARSEIP_EXPORTS
#define PARSEIP_API __declspec(dllexport)
#else
#define PARSEIP_API __declspec(dllimport)
#endif

// �����Ǵ� ParseIP.dll ������
#include "CReadQQWryDat/CReadQQWryDat.h"
class PARSEIP_API CParseIP 
{
public:
	CParseIP(void);
	~CParseIP(void);
	// TODO: �ڴ�������ķ�����

public:
	//�ӿں���
	void GetLoaclhostName(char* pszHostName);
	void GetLoaclhostIP(char* pszHostIP);
	void GetLocalIPInfo(char* pszLoaclIPInfo);
	void QueryIP2Addr(char* pszIP,char* pszAddr);
	CReadQQWryDat *m_pReadQQWryDat;
};

extern PARSEIP_API int nParseIP;

PARSEIP_API int fnParseIP(void);
