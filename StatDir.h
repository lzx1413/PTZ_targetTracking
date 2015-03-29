#pragma once
#include "browsedir.h"
class CStatDir :public CBrowseDir
{
protected:
	int m_nFileCount;   //保存文件个数
	int m_nSubdirCount; //保存子目录个数

public:
	CStatDir()
	{
		m_nFileCount = m_nSubdirCount = 0;
	}

	int GetFileCount()
	{
		return m_nFileCount;
	}

	int GetSubdirCount()
	{
		return m_nSubdirCount - 1;
	}

protected:
	virtual bool ProcessFile(const char *filename)
	{
		m_nFileCount++;
		return CBrowseDir::ProcessFile(filename);
	}

	virtual void ProcessDir
		(const char *currentdir, const char *parentdir)
	{
		m_nSubdirCount++;
		CBrowseDir::ProcessDir(currentdir, parentdir);
	}
};
