#pragma comment(lib,"wininet.lib") //remove if not using VC++.
#include <stdio.h>
#include <windows.h>
#include <wininet.h>

int main() {
	HINTERNET connect = InternetOpen("MyBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	char* website_address = "";

	if (!connect) {
		printf("Connection Failed or Syntax error");
		DWORD WINAPI GetLastError(void);
		return 0;
	}

	HINTERNET OpenAddress = InternetOpenUrl(connect, website_address, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

	if (!OpenAddress)
	{
		printf("\n%x\n", GetLastError());
		printf("Failed to open URL \n");
		InternetCloseHandle(connect);
		system("pause");
		return 0;
	}

	char DataReceived[4096];
	DWORD NumberOfBytesRead = 0;
	while (InternetReadFile(OpenAddress, DataReceived, 4096, &NumberOfBytesRead) && NumberOfBytesRead)
	{
		printf(DataReceived);
	}

	InternetCloseHandle(OpenAddress);
	InternetCloseHandle(connect);

	system("pause");
	return 0;
}
