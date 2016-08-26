#pragma comment(lib,"wininet.lib") //remove if not using VC++.
#include <stdio.h>
#include <windows.h>
#include <wininet.h>

int main() {
	char* website_address = "";
	DWORD dwAccessRequest = INTERNET_OPEN_TYPE_PRECONFIG;
	DWORD dwRequestFlags = INTERNET_SERVICE_HTTP | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_PRAGMA_NOCACHE;

	HINTERNET connect = InternetOpen("MyBrowser", dwAccessRequest, NULL, NULL, 0);

	if (!connect) {
		printf("Connection Failed or Syntax error");
		DWORD WINAPI GetLastError(void);
		return 0;
	}

	HINTERNET OpenAddress = InternetOpenUrl(connect, website_address, NULL, NULL, dwRequestFlags, NULL);

	if (!OpenAddress)
	{
		printf("Webpage:\t%s\n", website_address);
		printf("Error:\t0x%x\n", GetLastError());
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
