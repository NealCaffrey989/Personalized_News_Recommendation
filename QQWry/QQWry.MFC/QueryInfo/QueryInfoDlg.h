
// QueryInfoDlg.h : 头文件
//

#pragma once



#include "..\\ParseIP\\ParseIP.h"
#pragma comment(lib,"..\\Debug\\ParseIP.lib")
_declspec(dllimport) class CParseIP ;


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

// CQueryInfoDlg 对话框
class CQueryInfoDlg : public CDialogEx
{
// 构造
public:
	CQueryInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QUERYINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	CParseIP m_cParseIP;
	CString  m_strIP;//待查询的IP
	CString  m_strAddr;//查询的结果
	afx_msg void OnBnClickedBtnQueryIp();
};
