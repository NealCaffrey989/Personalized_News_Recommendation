/************************************************************************/
/* 
��ȡQQWry.dat�ļ���  

˵�� ��qqwry.dat���� res\  Ŀ¼��
*/
/************************************************************************/
#ifndef _CREAD_QQWRYDAT_H_
#define _CREAD_QQWRYDAT_H_

#include <fstream>
#include <iostream>
using namespace std;

#define SIZE_INDEX 7  //�����Ĵ�С��7 
#define MAX_BUF 50

//�����ײ��Ľṹ��
	//�ļ�ͷ
typedef struct _tagBE 
{
	int uBoff;
	int uEoff;
}stBE,*pBE;

typedef struct _tagEndInfo
{
	BYTE b0;
	BYTE b1;
	BYTE b2;
	BYTE b3;
	BYTE buf[MAX_BUF];
	BYTE bMode;
	int  iOffset1;
	int  iOffset2;
}stEndInfo,*PstEndInfo;

typedef struct _tagIPOff
{
	BYTE b0;
	BYTE b1;
	BYTE b2;
	BYTE b3;
	BYTE bOff1;
	BYTE bOff2;
	BYTE bOff3;
}stIPOff,*PstIPOff;

enum emTypePointerPos{ POS_BEGIN,POS_CUR,POS_END };//�ļ�ָ��λ��

class CReadQQWryDat
{
public:
	CReadQQWryDat(CString strDatPath);
	virtual ~CReadQQWryDat();

public:
	CString GetLoaclHostName();
	CString GetLoaclhostIP();//��ȡ����IP��������������Ϣ
	CString QueryIPInfo();//��ȡIP��ַ�����Ϣ
	CString QueryDatVersion();//��ȡDAT�汾
	CString QueryDatHeader();//��ȡ�ļ�ͷ��Ϣ
	void QueryIp2Addr(CString strIP,CString& strAddr);//ת��IP����ַ
	int		QueryRecordCount();//��ȡ��¼��
protected:
	fstream m_fs;
	void LoadQQWryDat(CString strDatPath);//�������ݿ��ļ�
	BOOL ParseQQWryDat();//�������ݿ��ļ�
	BOOL CloseQQWryDat();//�ر����ݿ��ļ�
	streampos GetQQWryDatFileSize();//��ȡ�ļ���С
	BOOL MoveReadPointer(streamoff offset,emTypePointerPos origin);//�ƶ���ָ��
	int ReadBytes(void* pBuf,const int& iBytes);//��ȡָ���ֽ���
	int QueryStartIPinfo(int iIndex);//��ȡ��ʼIP��Ϣ
	CString QueryCountryLocal(int iIndex);
	int  QueryIndex(CString strIP);
	CString QueryStr(int ioffset = 0);
	DWORD IP2DWORD(CString strIP);
	DWORD QuerySIP(int index);
private:
	stBE m_stBe;
	stEndInfo m_stEi;
	stIPOff	  m_stIpOff;
	DWORD     m_dwLastIP;
};

#endif