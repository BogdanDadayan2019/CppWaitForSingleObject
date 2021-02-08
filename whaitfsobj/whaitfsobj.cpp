
#include <iostream>
#include <windows.h>
using namespace std;

struct BgStruct
{
	int a;
	int b;

	HANDLE he;
	HANDLE xe;

};

DWORD WINAPI BgFunc(LPVOID lpParam) {
	

	BgStruct* bs = (BgStruct*)lpParam;

	while (true) {

		WaitForSingleObject(bs->xe, INFINITE);

		bs->b = bs->a * bs->a;

		cout << bs->a << endl;

		SetEvent(bs->he);

		ResetEvent(bs->xe);

	}

	return 0;

}

int main()
{

	BgStruct bg_struct;
	bg_struct.a = 7;
	bg_struct.b = 10;

	HANDLE bg_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	bg_struct.he = bg_event;

	HANDLE bg_event2 = CreateEvent(NULL, TRUE, FALSE, NULL);
	bg_struct.xe = bg_event2;

	CreateThread(NULL, 0, &BgFunc, &bg_struct, 0, NULL);
	
	

	int i = 0;

	while (true) 
	{

		if (i == 100) {
			break;
		}

		i++;

		bg_struct.a = i;
		SetEvent(bg_struct.xe);
		WaitForSingleObject(bg_struct.he, INFINITE);
		ResetEvent(bg_event);
		cout << "Loop" << endl;
		cout << bg_struct.b << endl;
	}

} 
