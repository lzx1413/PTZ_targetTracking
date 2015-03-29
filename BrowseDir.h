#pragma once
#include "direct.h"
#include "string.h"
#include "io.h"
#include "stdio.h" 
#include <vector>
#include <iostream>
using namespace std;
class CBrowseDir
{
protected:
	char m_szInitDir[_MAX_PATH];

public:
	CBrowseDir();
	bool SetInitDir(const char *dir);
	bool BeginBrowse(const char *filespec);
	vector<char*> BeginBrowseFilenames(const char *filespec);

protected:
	bool BrowseDir(const char *dir, const char *filespec);
	vector<char*> GetDirFilenames(const char *dir, const char *filespec);
	virtual bool ProcessFile(const char *filename);
	virtual void ProcessDir(const char *currentdir, const char *parentdir);
};