/************************************************************************/
/* 
读取QQWry.dat文件类  

说明 将qqwry.dat放在 res\  目录下
*/
/************************************************************************/
#ifndef _CREAD_QQWRYDAT_H_
#define _CREAD_QQWRYDAT_H_

#include <fstream>
#include <iostream>
using namespace std;

#define SIZE_INDEX 7  //索引的大小是7 
#define MAX_BUF 50

//定义首部的结构体
	//文件头
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

enum emTypePointerPos{ POS_BEGIN,POS_CUR,POS_END };//文件指针位置

class CReadQQWryDat
{
public:
	CReadQQWryDat(CString strDatPath);
	virtual ~CReadQQWryDat();

public:
	CString GetLoaclHostName();
	CString GetLoaclhostIP();//获取本机IP和网络适配器信息
	CString QueryIPInfo();//获取IP地址相关信息
	CString QueryDatVersion();//获取DAT版本
	CString QueryDatHeader();//获取文件头信息
	void QueryIp2Addr(CString strIP,CString& strAddr);//转换IP到地址
	int		QueryRecordCount();//获取记录数
protected:
	fstream m_fs;
	void LoadQQWryDat(CString strDatPath);//加载数据库文件
	BOOL ParseQQWryDat();//解析数据库文件
	BOOL CloseQQWryDat();//关闭数据库文件
	streampos GetQQWryDatFileSize();//获取文件大小
	BOOL MoveReadPointer(streamoff offset,emTypePointerPos origin);//移动读指针
	int ReadBytes(void* pBuf,const int& iBytes);//读取指定字节数
	int QueryStartIPinfo(int iIndex);//获取开始IP信息
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