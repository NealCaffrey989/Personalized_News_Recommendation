
// QueryInfoDlg.h : ͷ�ļ�
//

#pragma once



#include "..\\ParseIP\\ParseIP.h"
#pragma comment(lib,"..\\Debug\\ParseIP.lib")
_declspec(dllimport) class CParseIP ;


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

// CQueryInfoDlg �Ի���
class CQueryInfoDlg : public CDialogEx
{
// ����
public:
	CQueryInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QUERYINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	CParseIP m_cParseIP;
	CString  m_strIP;//����ѯ��IP
	CString  m_strAddr;//��ѯ�Ľ��
	afx_msg void OnBnClickedBtnQueryIp();
};
