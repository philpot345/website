#pragma comment(lib,"wininet.lib") //remove if not using VC++.
#include <stdio.h>
#include <windows.h>
#include <wininet.h>

int main() {
	char DataReceived[4096];

	DWORD dwAddressRequestFlags = INTERNET_FLAG_KEEP_CONNECTION;// | INTERNET_FLAG_PRAGMA_NOCACHE;
	DWORD dwConnectionAccessRequest = INTERNET_OPEN_TYPE_PRECONFIG;
	DWORD dwConnectionFlags = 0;//INTERNET_FLAG_ASYNC;
	DWORD dwNumberofBytesRead = 0;

	LPWSTR website_address = TEXT("");

	HINTERNET hConnect = NULL, hInternetConnect = NULL, hOpenAddress = NULL;

	hConnect = InternetOpen("MyBrowser", dwConnectionAccessRequest, NULL, NULL, dwConnectionFlags);

	if (!hConnect) {
		printf("Failed to make base connection\n");
		printf("Connection Failed or Syntax error");
		DWORD WINAPI GetLastError(void);
		return 0;
	}
	else
		printf("Server Connection Successful:\t0x%x\n", hConnect);

	hInternetConnect = InternetConnect(hConnect, website_address, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	if (!hInternetConnect)
	{
		printf("Webpage:\t%s\n", website_address);
		printf("Failed to make internet connection\n");
		printf("Error:\t0x%x\n", GetLastError());
		printf("Failed to open URL \n");
		InternetCloseHandle(hConnect);
		system("pause");
		return 0;
	}

	else
		printf("Internet Connection Successful:\t0x%x\n", hInternetConnect);

	hOpenAddress = InternetOpenUrl(hConnect, website_address, NULL, NULL, dwAddressRequestFlags, NULL);

	if (!hOpenAddress)
	{
		printf("Webpage:\t%s\n", website_address);
		printf("Failed to open website\n");
		printf("Error:\t0x%x\n", GetLastError());
		printf("Failed to open URL \n");
		InternetCloseHandle(hInternetConnect);
		InternetCloseHandle(hConnect);
		system("pause");
		return 0;
	}

	else
		printf("Connection to URL Successful:\t0x%x\n", hOpenAddress);
	/*
	dwNumberofBytesRead = 0;
	while (InternetReadFile(hOpenAddress, DataReceived, 4096, &dwNumberofBytesRead) && dwNumberofBytesRead)
	{
		printf(DataReceived);
	}

	InternetCloseHandle(hOpenAddress);
	InternetCloseHandle(hInternetConnect);
	InternetCloseHandle(hConnect);
	*/
	system("pause");
	return 0;
}
