#include "path.h"

Path::Path()
{
	sPath = ".";
	bRecursive = false;
}

string Path::Load()
{
	char pError[64] = {0};

	vPaths.clear();
	vDirs.clear();
	vFiles.clear();

	if(exists(sPath))
	{
		LoadPaths();
		LoadDirs();
		LoadFiles();
	}
	else
		sprintf(pError, "Error, path not found: '%s'", sPath.c_str());

	return string(pError);
}

void Path::LoadPaths()
{
	if(bRecursive)
	{
		for(auto &de : recursive_directory_iterator(sPath))
			vPaths.push_back(de.path());
	}

	else
	{
		for(auto &de : directory_iterator(sPath))
			vPaths.push_back(de.path());
	}

	if(vPaths.size() > 1)
		sort(vPaths.begin(), vPaths.end());
}

void Path::LoadDirs()
{
	if(bRecursive)
	{
		for(auto &de : recursive_directory_iterator( sPath ))
		{
			if(is_directory(de.path()))
				vDirs.push_back(de.path());
		}
	}

	else
	{
		for(auto &de : directory_iterator( sPath ))
		{
			if(is_directory(de.path()))
				vDirs.push_back(de.path());
		}
	}
	sort(vDirs.begin(), vDirs.end());
}

void Path::LoadFiles()
{
	if(bRecursive)
	{
		for(auto &de : recursive_directory_iterator(sPath))
		{
			if(is_regular_file(de.path()) && sExtensions.count(de.path().extension().generic_string()))
				vFiles.push_back(de.path());
		}
	}
	else
	{
		for(auto &de : directory_iterator(sPath))
		{
			if(is_regular_file(de.path()))
				vFiles.push_back(de.path());
		}
	}
	sort(vFiles.begin(), vFiles.end());
}

string Path::StrPaths()
{
	string s;
	int end = vPaths.size();
	int i = 0;
	for(auto & pe : vPaths)
	{
		s += pe.string();
		if(++i != end)	s += '\n';
	}

	return s;
}

string Path::StrDirs()
{
	string s;
	int end = vDirs.size();
	int i = 0;
	for(auto & pe : vDirs)
	{
		s += pe.string();
		if(++i != end)	s += '\n';
	}

	return s;
}

string Path::StrFiles()
{
	string s;
	int end = vFiles.size();
	int i = 0;
	for(auto & pe : vFiles)
	{
		s += pe.string();
		if(++i != end)	s += '\n';
	}

	return s;
}
