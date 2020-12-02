#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include "path.h"
#include "timer.h"
using namespace std;
int FilesProcessed = 0;

void doreplaygain(vector<path> vFileSplit)
{
	for(long unsigned int i = 0; i < vFileSplit.size(); i++)
	{
		if(vFileSplit[i].extension() == ".mp3")
			system(("mid3v2 -C \"" + vFileSplit[i].generic_string() + "\"").c_str());		// Convert ID3v1 tag to ID3v2 for use with replaygain
		system(("replaygain \"" + vFileSplit[i].generic_string() + "\"").c_str());
		FilesProcessed++;
	}
}

int main(int argc, char *argv[])
{
	Timer tTimer;
	tTimer.Start();
	int ThreadCount = thread::hardware_concurrency();
	if(ThreadCount == 0) ThreadCount = 12;

	Path *pPath = new Path;
	pPath->sExtensions = set<string> { ".mp3", ".ogg" };
	string sError;
	cout << "Loading input file list..." << endl;
	if(argc > 1)
	{	pPath->sPath = argv[1];
		pPath->bRecursive = true;
		sError = pPath->Load();
		if(sError != "")
		{
			cerr << sError << endl;
			return 1;
		}
	}
	else
	{
		cerr << "Please specify an input path." << endl;
		return 1;
	}
	vector<vector<path>> vFileSplit(ThreadCount, vector<path>());
	for(long unsigned int i = 0; i < pPath->vFiles.size(); i++)
		vFileSplit[i % ThreadCount].push_back(pPath->vFiles[i]);
	vector<thread> Threads;
    for(int i = 0; i < ThreadCount; i++)
    {
    	thread T(doreplaygain, vFileSplit[i]);
        Threads.push_back(move(T));
    }
    for(auto &T : Threads)
    {
    	T.join();
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Files Processed:       " << FilesProcessed << endl;
    tTimer.Stop();
    cout << "Time Elapsed:          " << tTimer.Delta << " seconds" << endl;
    cout << "Average Time Per File: " << tTimer.Delta / (float)FilesProcessed << " seconds" << endl;
	delete pPath;
	return 0;
}
