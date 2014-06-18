/*
IDENT HEADER
Author: Jim Haight
Class: 4002-212
Assignment: Practice 5
*/
#include <cstdlib>
#include <iostream>

#include <Windows.h>
#include <string.h>
#include <unistd.h>

using namespace std;

//thread code
DWORD WINAPI StartThread(LPVOID iValue)
{
	char lszParam[3];
	strcpy(lszParam,(char *)iValue);
	int iStart = atoi(lszParam);
	int sleeptime = 0;
    srand(time(0));

	for(int i = 1; i <= 100; i++){
		sleeptime = (rand() % 100)+100;
		cout << "threadID: " << iStart << " number: " << i << " sleeptime: " << sleeptime << endl;
		Sleep(sleeptime);
	}


	return 0;
}
int main()
{
	//HANDLE
	HANDLE hThread1,hThread2,hThread3,hThread4,hThread5;
	//uhm... maybe?
//	HANDLE maybe[] = {hThread1,hThread2,hThread3,hThread4,hThread5};
//NOPE
    //DWORD
	DWORD dwGenericThread;
	//char array
	char lszThreadParam1[3];
	char lszThreadParam2[3];

	char lszThreadParam3[3];

	char lszThreadParam4[3];

	char lszThreadParam5[3];

	
	/*
	CreateThread
	   CreateThread( 
		NULL,                   // default security attributes
		0,                      // use default stack size  
		StartThread,       // thread function name
		pDataArray[i],          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[i]);   // returns the thread identifier 
	 http://msdn.microsoft.com/en-us/library/ms682453%28v=vs.85%29.aspx
	   
	*/
	strcpy(lszThreadParam1,"1");
	hThread1 = CreateThread(NULL,0,StartThread,&lszThreadParam1,0,&dwGenericThread);
	//test that hThread was created
	if(hThread1 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return 1;
	}
	//block until thread completes
	//WaitForSingleObject(hThread1,INFINITE);
strcpy(lszThreadParam2,"2");
	hThread2 = CreateThread(NULL,0,StartThread,&lszThreadParam2,0,&dwGenericThread);
	//test that hThread was created
	if(hThread2 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return 1;
	}
	
	strcpy(lszThreadParam3,"3");
	hThread3 = CreateThread(NULL,0,StartThread,&lszThreadParam3,0,&dwGenericThread);
	//test that hThread was created
	if(hThread3 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return 1;
	}
	strcpy(lszThreadParam4,"4");
	hThread4 = CreateThread(NULL,0,StartThread,&lszThreadParam4,0,&dwGenericThread);
	//test that hThread was created
	if(hThread4 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return 1;
	}
strcpy(lszThreadParam5,"5");
	hThread5 = CreateThread(NULL,0,StartThread,&lszThreadParam5,0,&dwGenericThread);
	//test that hThread was created
	if(hThread5 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return 1;
	}
	
	
	WaitForSingleObject(hThread1,INFINITE);
	WaitForSingleObject(hThread2,INFINITE);
	WaitForSingleObject(hThread3,INFINITE);
	WaitForSingleObject(hThread4,INFINITE);
	WaitForSingleObject(hThread5,INFINITE);
	//WaitForMultipleObjects(5,maybe,TRUE,INFINITE);
	system("PAUSE");
	return 0;
}
