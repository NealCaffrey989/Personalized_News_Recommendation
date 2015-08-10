#include "stdafx.h"

#include "CReadQQWryDat.h"

CReadQQWryDat::CReadQQWryDat(CString strDatPath){
	memset(&m_stBe,0,sizeof(stBE));
	LoadQQWryDat(strDatPath);
	if (FALSE == ParseQQWryDat())	{
		return;
	}	
}
CReadQQWryDat::~CReadQQWryDat(){
	if (m_fs)	{
		CloseQQWryDat();
	}
}
/************************************************************************/
/* 
返回本地主机名称
*/
/************************************************************************/
CString CReadQQWryDat::GetLoaclHostName()
{
	CString strHostName;
	//////////////// 
	WORD   wVersionRequested   =   MAKEWORD(2,2); 
	WSADATA   wsaData; 
	if(WSAStartup(wVersionRequested,   &wsaData)) { 
		return   strHostName; 
	} 

	////////////////// 
	//   获得主机名. 
	// 
	char  hostname[MAX_PATH]; 
	int   res = gethostname(hostname, sizeof(hostname)); 
	if   (res !=  0)
	{ 		
		return   strHostName; 
	} 

	strHostName = hostname;
	return strHostName;
}

/************************************************************************/
/* 
获取本机IP地址 
*/
/************************************************************************/
CString CReadQQWryDat:: GetLoaclhostIP()
{
	CString str;	
	CString strHostName = GetLoaclHostName();
	char* hostname = strHostName.GetBuffer(0);
	hostent*   pHostent   =   gethostbyname(hostname); 
	if   (pHostent==NULL)   
	{ 
		return str;
	} 
	//   解析返回的hostent信息. 
	hostent&   he   =   *pHostent; 
// 	str.Format( "\nname=%s \naliases=%s\naddrtype=%d\nlength=%d\n", 
// 		he.h_name,he.h_aliases,he.h_addrtype,he.h_length); 

	
	sockaddr_in   sa; 
	for(int nAdapter=0; he.h_addr_list[nAdapter];nAdapter++)
	{ 
		memcpy(&sa.sin_addr.s_addr,he.h_addr_list[nAdapter],he.h_length); 
		//   输出机器的IP地址. 	
		CString strtemp;
		strtemp.Format( "%s\n",inet_ntoa(sa.sin_addr)); 
		str += strtemp;
		strtemp = "";
	} 
	//   终止   Windows   sockets   API 
	WSACleanup(); 
	return str;
}

/************************************************************************/
/* 
查询根据给定的IP地址对应的信息  未添加
*/
/************************************************************************/
CString CReadQQWryDat::QueryIPInfo()
{
	CString str;
	return str;
}
/************************************************************************/
/* 
查询数据库版本信息
*/
/************************************************************************/
CString CReadQQWryDat::QueryDatVersion()
{
	CString str;
	MoveReadPointer(0,POS_CUR);//设置读取的位置
	return str;
}

/************************************************************************/
/* 
//获取文件头(索引绝对偏移(8 字节) = 第一条索引偏移(4 字节) + 第二条索引偏移(4 字节))信息 
*/
/************************************************************************/
CString CReadQQWryDat::QueryDatHeader()
{
	CString str;
	str.Format("第一条索引偏移值为: %d\n最后一条索引偏移值为: %d",m_stBe.uBoff,m_stBe.uEoff);
	return str;
}
/************************************************************************/
/* 
获取记录数
*/
/************************************************************************/
int CReadQQWryDat::QueryRecordCount()
{
	if (m_stBe.uEoff < m_stBe.uBoff) return 0;
	
	return (m_stBe.uEoff-m_stBe.uBoff)/SIZE_INDEX+1;
}
/************************************************************************/
/* 
IP转换为地址
*/
/************************************************************************/
void CReadQQWryDat::QueryIp2Addr(CString strIP,CString& strAddr)
{
	if (strIP == "") return;
	if (strIP == "127.0.0.1")
	{
		strAddr = "本地主机";
		return;
	}
	strAddr = QueryCountryLocal(QueryIndex(strIP));
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//私有函数区
//加载数据库文件
void CReadQQWryDat::LoadQQWryDat(CString strDatPath)
{
	m_fs.open(strDatPath,ios::binary|ios::in,_SH_DENYRD);	//2进制打开
}
//解析数据库文件
BOOL CReadQQWryDat::ParseQQWryDat(){
	MoveReadPointer(0,POS_BEGIN);//移动到文件头
	if (ReadBytes(&m_stBe,8) != 8){
		return FALSE;
	}
	
	if (m_stBe.uEoff == 0 || m_stBe.uBoff == 0){
		return FALSE;
	}
	return TRUE;
}
//关闭数据库文件
BOOL CReadQQWryDat::CloseQQWryDat()
{
	m_fs.close();
	return TRUE;
}

//获取文件大小
streampos CReadQQWryDat::GetQQWryDatFileSize()
{
	m_fs.seekg(0, ios::end);    
	streampos ps = m_fs.tellg();
	return ps;
}
//设置要读取的指针到指定的位置
BOOL CReadQQWryDat::MoveReadPointer(streamoff offset,emTypePointerPos iType)
{
	if (offset > GetQQWryDatFileSize())
	{
		return FALSE;
	}
	switch(iType)
	{
	case POS_BEGIN:
		m_fs.seekg(offset,ios::beg);
		break;
	case POS_CUR:
		m_fs.seekg(offset,ios::cur);
		break;
	case POS_END:
		m_fs.seekg(offset,ios::end);
		break;
	default:
		break;
	}
	return TRUE;
}

//读取指定个数的字节到 pbuf中
int CReadQQWryDat::ReadBytes(void*  pBuf,const int& iBytes)
{
	m_fs.read((char*)pBuf,iBytes);
	return m_fs.gcount();
}

//获取开始Ip偏移
int  CReadQQWryDat::QueryStartIPinfo(int iIndex)
{
	BYTE buf[MAX_BUF];
	int iOffset;
	iOffset = m_stBe.uBoff + iIndex*7;
	if(iOffset > m_stBe.uEoff) return 0;
	MoveReadPointer(iOffset,POS_BEGIN);
	ReadBytes(&m_stIpOff,sizeof(stIPOff));
	iOffset = (m_stIpOff.bOff1 + m_stIpOff.bOff2*256 + m_stIpOff.bOff3*256*256);
	MoveReadPointer(iOffset,POS_BEGIN);
	ReadBytes(&m_stEi,sizeof(stEndInfo));

	if (m_stEi.buf[0] != 1 && m_stEi.buf[0] != 2)
	{
		m_stEi.bMode = 1;//没有跳
		for (int i=0;i<MAX_BUF;i++)
		{
			if (m_stEi.buf[i] == 0)
			{
				if (m_stEi.buf[i+2] == 2)
				{
					m_stEi.bMode = 2;//Local跳
					m_stEi.iOffset1 = m_stEi.buf[i+2] +
					m_stEi.buf[i+3]*256 + 
					m_stEi.buf[i+4]*256*256;
				}
				break;
			}
		}
	}
	else if (m_stEi.buf[0] == 2)
	{
		m_stEi.bMode = 3;//Country跳 Local不跳
		m_stEi.iOffset1 = m_stEi.buf[1] + 
						  m_stEi.buf[2]*256 +
						  m_stEi.buf[3]*256*256;
		if (m_stEi.buf[4] != 2)
		{
			m_stEi.bMode = 3;
		}
		else
		{
			m_stEi.bMode = 4;//Country跳 Local也跳
			m_stEi.iOffset2 = m_stEi.buf[5] +
							  m_stEi.buf[6]*256 +
							  m_stEi.buf[7]*256*256;
		}
	}
	else if (m_stEi.buf[0] == 1)
	{
		m_stEi.iOffset1 = m_stEi.buf[1] +m_stEi.buf[2]*256 + m_stEi.buf[3]*256*256;
		MoveReadPointer(m_stEi.iOffset1,POS_BEGIN);
		ReadBytes(buf,MAX_BUF);
		memcpy(m_stEi.buf,buf,MAX_BUF);
		m_stEi.bMode = 0;

		for (int i=0;i<MAX_BUF;i++)
		{
			if (m_stEi.buf[i] == 0)
			{
					if (m_stEi.buf[i+1] != 2)
					{
						m_stEi.bMode = 5;//1没有跳
					}
					else
					{
						m_stEi.bMode = 6;//1 Country不跳 Local跳
						m_stEi.iOffset2 = m_stEi.buf[i+2] +
										  m_stEi.buf[i+3]*256+
										  m_stEi.buf[i+4]*256*256;
					}
				break;
			}			
		}
	}
	else
	{
		if (m_stEi.buf[4] != 2)
		{
			m_stEi.bMode = 7;//1 Country 跳 Local 不跳
			m_stEi.iOffset2 = m_stEi.buf[1] +
								m_stEi.buf[2]*256 +
								m_stEi.buf[3]*256*256;
		}
		else
		{
			m_stEi.bMode = 8;//1 Country跳 Local跳
			m_stEi.iOffset1 = m_stEi.buf[1] +
								m_stEi.buf[2]*256 +
								m_stEi.buf[3]*256*256;
			m_stEi.iOffset2 = m_stEi.buf[5] +
				m_stEi.buf[6]*256 +
				m_stEi.buf[7]*256*256;
		}
	}	
	return iOffset;
}

CString CReadQQWryDat::QueryCountryLocal(int iIndex)
{ 
	CString str;
	int iOffset = 4+QueryStartIPinfo(iIndex);
	if (iIndex < 0 || iIndex > QueryRecordCount()-1)
	{
		str = "未知IP地址!\n";
		return str;
	}
	else
	{
		switch (m_stEi.bMode)
		{
		case 1://X没有跳
			{
				str = QueryStr(iOffset);
				str += "";
				str +=QueryStr();
			}
			break;
		case 2://X Country不跳 Local跳
			{
				str = QueryStr(iOffset);
				str += "";
				str +=QueryStr(m_stEi.iOffset1);
			}			
			break;
		case 3://2 Country跳 Local不跳
			{
				str = QueryStr(m_stEi.iOffset1);
				str +="";
				str += QueryStr(iOffset+4);
			}
			break;
		case 4://2 Country跳 Local跳
			{
				str = QueryStr(m_stEi.iOffset1);
				str += "";
				str += QueryStr(m_stEi.iOffset2);
			}
			break;
		case 5://1 没有跳
			{
				str = QueryStr(m_stEi.iOffset1);
				str += "";
				str += QueryStr();
			}
			break;
		case 6: //1 Country不跳 Local跳
			{
				str = QueryStr(m_stEi.iOffset1);
				str += "";
				str += QueryStr(m_stEi.iOffset2);
			}
			break;
		case 7://1 Country跳 Local不跳
			{
				str = QueryStr(m_stEi.iOffset2);
				str += "";
				str += QueryStr(m_stEi.iOffset1 + 4);
			}
			break;
		case 8:
			{
				str = QueryStr(m_stEi.iOffset1);
				str += "";
				str += QueryStr(m_stEi.iOffset2);
			}
			break;
		default:
			break;
		}
	}
	return str;
}

//半跳检索法查询
int CReadQQWryDat::QueryIndex(CString strIP)
{
	int index = -1;
	DWORD dwInputIP;
	DWORD dwStartIP;
	dwInputIP = IP2DWORD(strIP);

	//顺序查找
	/*
	if (dwInputIP<=0x7FFFFFFF)
	for (int i=0;i<QueryRecordCount();i++)
	{
		dwStartIP = QuerySIP(i);
		if (dwStartIP<=dwInputIP && dwInputIP<=m_dwLastIP)
		{
			index = i;
			break;
		}
	}
	else
	for(int i=QueryRecordCount()-1;i>=0;i--)
	{
		dwStartIP = QuerySIP(i);
		if (dwStartIP <=dwInputIP && dwInputIP <= m_dwLastIP)
		{
			index = i;
			break;
		}
	}
	*/

	//半跳法
	int iT;
	int iB,iE;
	iB = 0;
	iE = QueryRecordCount()-1;
	iT = iE/2;

	while(iB<iE)
	{
		dwStartIP = QuerySIP(iT);
		if (dwInputIP == dwStartIP)
		{
			index = iT;
			break;
		}
		if ((iE-iB) <= 1)
		{
			for (int i=iB;i<=iE;i++)
			{
				dwStartIP = QuerySIP(i);
				if (dwStartIP <= dwInputIP && dwInputIP <= m_dwLastIP )
				{
					index = i;
					break;
				}
			}
			break;
		}
		if (dwInputIP > dwStartIP)
		{
			iB = iT;
		}
		else
		{
			iE = iT;
		}
		iT = iB + (iE-iB)/2;
	}
	return index;
}

//获取指定偏移地址的字符
CString CReadQQWryDat::QueryStr(int ioffset/* = 0*/)
{
	CString str;
	if (ioffset>m_stBe.uEoff)
		return str;
	BYTE ch;
	if (ioffset)  //若偏移量不为0 则表示获取相对于文件头的字符
	{
		MoveReadPointer(ioffset,POS_BEGIN);
	}	
	int i = 0;
	while (TRUE)
	{
		if (ReadBytes(&ch,1) == 0)
		{
			return str;
		}		
		if (ch == 0)
		{
			break;
		}
		str += ch;
		i++;
		if (i>50)	break;
	}
	return str;
}

//
DWORD CReadQQWryDat::QuerySIP(int index)
{
	DWORD dwIP;
	BYTE b[3];
	int iOffset;
	if (index>QueryRecordCount()-1) return -1;
	if (index<0) return -1;
	iOffset = m_stBe.uBoff + index*SIZE_INDEX;
	MoveReadPointer(iOffset,POS_BEGIN);
	ReadBytes(&dwIP,4);
	ReadBytes(b,3);
	iOffset = b[0]+b[1]*256+b[2]*256*256;
	MoveReadPointer(iOffset,POS_BEGIN);
	ReadBytes(&m_dwLastIP,4);
	return dwIP;
}

//转换字符串IP地址到DWORD类型
DWORD CReadQQWryDat::IP2DWORD(CString strIP)
{
	DWORD dwIP;
	BYTE  b[4];
	CString strTemp;
	char ch;
	int iLen;
	int iXB;
	strIP += ".";
	memset(b,0,4);
	iLen = strIP.GetLength();
	iXB = 0;
	dwIP = 0;
	for (int i=0;i<iLen;i++)
	{
		ch = strIP.GetAt(i);
		strTemp += ch;
		if ('.' == ch)
		{
			b[iXB] = atoi(strTemp);
			strTemp = "";
			iXB++;
		}
	}
	dwIP = b[0]*256*256*256 + b[1]*256*256+b[2]*256+b[3];
	return dwIP;
	
}