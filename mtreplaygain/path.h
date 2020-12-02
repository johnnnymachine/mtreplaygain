#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <set>

using namespace std;
using namespace boost::filesystem;

class Path
{
public:
	string sPath;
	set<string> sExtensions;
	vector<path> vPaths;
	vector<path> vDirs;
	vector<path> vFiles;
	bool bRecursive;

	Path();

	string Load();
	void LoadPaths();
	void LoadDirs();
	void LoadFiles();
	string StrPaths();
	string StrDirs();
	string StrFiles();

};


#endif /* PATH_H_ */
