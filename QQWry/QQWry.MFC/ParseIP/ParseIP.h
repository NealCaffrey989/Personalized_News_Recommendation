// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 PARSEIP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// PARSEIP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef PARSEIP_EXPORTS
#define PARSEIP_API __declspec(dllexport)
#else
#define PARSEIP_API __declspec(dllimport)
#endif

// 此类是从 ParseIP.dll 导出的
#include "CReadQQWryDat/CReadQQWryDat.h"
class PARSEIP_API CParseIP 
{
public:
	CParseIP(void);
	~CParseIP(void);
	// TODO: 在此添加您的方法。

public:
	//接口函数
	void GetLoaclhostName(char* pszHostName);
	void GetLoaclhostIP(char* pszHostIP);
	void GetLocalIPInfo(char* pszLoaclIPInfo);
	void QueryIP2Addr(char* pszIP,char* pszAddr);
	CReadQQWryDat *m_pReadQQWryDat;
};

extern PARSEIP_API int nParseIP;

PARSEIP_API int fnParseIP(void);
