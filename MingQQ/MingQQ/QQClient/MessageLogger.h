#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include "../SQLite 3.8.6/include/sqlite3.h"	// 使用sqlite3需要包含的头文件

#pragma comment(lib, "SQLite 3.8.6/lib/sqlite3.lib")

#if defined(UNICODE) || defined(_UNICODE)
	typedef std::wstring tstring;
#else
	typedef std::string tstring;
#endif

struct BUDDY_MSG_LOG		// 好友消息记录
{
	UINT nID;
	UINT nQQNum;
	tstring strNickName;
	UINT nTime;
	BOOL bSendFlag;
	tstring strContent;
};

struct GROUP_MSG_LOG		// 群消息记录
{
	UINT nID;
	UINT nGroupNum;
	UINT nQQNum;
	tstring strNickName;
	UINT nTime;
	tstring strContent;
};

struct SESS_MSG_LOG			// 临时会话(群成员)消息记录
{
	UINT nID;
	UINT nQQNum;
	tstring strNickName;
	UINT nTime;
	BOOL bSendFlag;
	tstring strContent;
};

void CloneStr(const wchar_t * src, wchar_t ** dest, UINT * destlen);

class CMessageLogger
{
public:
	CMessageLogger(void);
	~CMessageLogger(void);

public:
	tstring GetMsgLogFileName();						// 获取消息记录文件名称
	void SetMsgLogFileName(LPCTSTR lpszFileName);		// 设置消息记录文件名称

	BOOL IsMsgLogFileValid();							// 判断消息记录文件是否有效
	BOOL CreateMsgLogFile();							// 创建消息记录文件

	BOOL WriteBuddyMsgLog(UINT nQQNum, LPCTSTR lpNickName,	// 写入一条好友消息记录
		UINT nTime, BOOL bSendFlag, LPCTSTR lpContent);
	BOOL WriteGroupMsgLog(UINT nGroupNum, UINT nQQNum,		// 写入一条群消息记录
		LPCTSTR lpNickName, UINT nTime, LPCTSTR lpContent);
	BOOL WriteSessMsgLog(UINT nQQNum, LPCTSTR lpNickName,	// 写入一条临时会话(群成员)消息记录
		UINT nTime, BOOL bSendFlag, LPCTSTR lpContent);

	BOOL WriteBuddyMsgLog(BUDDY_MSG_LOG * lpMsgLog);	// 写入一条好友消息记录
	BOOL WriteGroupMsgLog(GROUP_MSG_LOG * lpMsgLog);	// 写入一条群消息记录
	BOOL WriteSessMsgLog(SESS_MSG_LOG * lpMsgLog);		// 写入一条临时会话(群成员)消息记录

	UINT ReadBuddyMsgLog(UINT nQQNum, UINT nOffset,		// 读出一条或多条好友消息记录
		UINT nRows, std::vector<BUDDY_MSG_LOG *>& arrMsgLog);
	UINT ReadGroupMsgLog(UINT nGroupNum, UINT nOffset,	// 读出一条或多条群消息记录
		UINT nRows, std::vector<GROUP_MSG_LOG *>& arrMsgLog);
	UINT ReadSessMsgLog(UINT nQQNum, UINT nOffset,		// 读出一条或多条临时会话(群成员)消息记录
		UINT nRows, std::vector<SESS_MSG_LOG *>& arrMsgLog);

	UINT GetBuddyMsgLogCount(UINT nQQNum);				// 获取好友消息记录数
	UINT GetGroupMsgLogCount(UINT nGroupNum);			// 获取群消息记录数
	UINT GetSessMsgLogCount(UINT nQQNum);				// 获取临时会话(群成员)消息记录数

	BOOL DelAllBuddyMsgLog();							// 删除所有好友消息记录
	BOOL DelAllGroupMsgLog();							// 删除所有群消息记录
	BOOL DelAllSessMsgLog();							// 删除所有临时会话(群成员)消息记录

	BOOL DelBuddyMsgLog(UINT nQQNum);					// 删除指定好友的所有消息记录
	BOOL DelGroupMsgLog(UINT nGroupNum);				// 删除指定群的所有消息记录
	BOOL DelSessMsgLog(UINT nQQNum);					// 删除指定临时会话(群成员)的所有消息记录

	BOOL DelBuddyMsgLogByID(UINT nID);					// 删除指定ID的好友消息记录
	BOOL DelGroupMsgLogByID(UINT nID);					// 删除指定ID的群消息记录
	BOOL DelSessMsgLogByID(UINT nID);					// 删除指定ID的临时会话(群成员)消息记录

	void Lock();										// 加锁函数
	void UnLock();										// 解锁函数

	// 待添加接口：
	// 1、根据某段时间、指定内容读出消息记录
	// 2、根据某段时间删除消息记录

private:
	UINT ReadBuddyMsgLogCount(UINT nQQNum, UINT nOffset, UINT nRows);
	UINT ReadGroupMsgLogCount(UINT nGroupNum, UINT nOffset, UINT nRows);
	UINT ReadSessMsgLogCount(UINT nQQNum, UINT nOffset, UINT nRows);

	void Replace(tstring& strText, const TCHAR * lpOldStr, const TCHAR * lpNewStr);

private:
	tstring m_strFileName;
	HANDLE m_hMutex;
};
