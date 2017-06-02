#include <windows.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int count = 0;
int processing = 0;

HANDLE ghMutex;
HANDLE hand1;
HANDLE hand2;

DWORD WINAPI Producer(LPVOID param)
{
	int rdn;
	DWORD dwWaitResult;
	while(true)
	{
		rdn = rand() % 1000 + 1;
		Sleep(rdn);

		dwWaitResult = WaitForSingleObject(ghMutex,INFINITE);

		if (dwWaitResult == WAIT_OBJECT_0)
		{
			count++;
			cout<<"写者 +1. 总数 = " << count << endl;
			ReleaseMutex(ghMutex);
		}
	}
	return 0;
}

DWORD WINAPI Consumer(LPVOID param)
{
	int rdn;
	DWORD dwWaitResult;
	while(true)
	{
		rdn = rand() % 1000 + 1;
		Sleep(rdn);
		if( count > 0)
		{
			dwWaitResult = WaitForSingleObject(ghMutex,INFINITE);
			if (dwWaitResult == WAIT_OBJECT_0)
			{
				count--;
				cout<<"读者 -1. 总数 = " << count << endl;
				ReleaseMutex(ghMutex);
			}
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int input=0;

	ghMutex = CreateMutex(
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);

	hand1=CreateThread (NULL, 0, Producer, (void*)&input, CREATE_SUSPENDED, NULL);
	hand2=CreateThread (NULL, 0, Consumer, (void*)&input, CREATE_SUSPENDED, NULL);

	ResumeThread(hand1);
	ResumeThread(hand2);

	while(true){
		cin>>input;
		if (input == 0)
			exit(0);
	};
	return 0;
}
