#define COUNT 11264

#pragma comment(lib,"wininet.lib") //remove if not using VC++.
#include <stdio.h>
#include <windows.h>
#include <wininet.h>

int uClose_Internet_Connections(HINTERNET, HINTERNET, HINTERNET);
int uConnect_to_Internet(HINTERNET, LPCWSTR, DWORD, DWORD);
int uConnect_to_Server(HINTERNET, HINTERNET, LPCWSTR, DWORD, DWORD);
int uConnect_to_URL(HINTERNET, HINTERNET, HINTERNET, LPCWSTR, DWORD);
int uPreform_Checks();
int uRead_Data_from_Website(HINTERNET, char[COUNT], int, DWORD);

int main() {

	//	Setup all Variables to be used

	char DataReceived[COUNT];

	int DataSize = COUNT;

	DWORD dwAddressRequestFlags = INTERNET_FLAG_KEEP_CONNECTION;// | INTERNET_FLAG_PRAGMA_NOCACHE;
	DWORD dwConnectionAccessRequest = INTERNET_OPEN_TYPE_PRECONFIG;
	DWORD dwConnectionFlags = 0;//INTERNET_FLAG_ASYNC;
	DWORD dwDefaultPort = INTERNET_DEFAULT_HTTP_PORT;
	DWORD dwInternetService = INTERNET_SERVICE_HTTP;
	DWORD dwNumberofBytesRead = 0;

	LPCWSTR application_title = TEXT("MyBrowser");
	LPCWSTR website_address = TEXT("");

	HINTERNET hConnect = NULL, hInternetConnect = NULL, hOpenAddress = NULL;

	//	Open a connection to the internet
	hConnect = uConnect_to_Internet(hConnect, application_title, dwConnectionAccessRequest, dwConnectionFlags);

	//	Open a connection to the server / address
	hInternetConnect = uConnect_to_Server(hConnect, hInternetConnect, website_address, dwDefaultPort, dwInternetService);

	//	Connect to the URL
	hOpenAddress = uConnect_to_URL(hConnect, hInternetConnect, hOpenAddress, website_address, dwAddressRequestFlags);

	//	Perform the actions
	uRead_Data_from_Website(hOpenAddress, DataReceived, DataSize, dwNumberofBytesRead);

	//	Perform the checks

	uPreform_Checks();

	//	Close all internet connections
	uClose_Internet_Connections(hConnect, hInternetConnect, hOpenAddress);

	system("pause");
	return 0;
}

int uClose_Internet_Connections(hConnect, hInternetConnect, hOpenAddress)
{
	InternetCloseHandle(hOpenAddress);
	InternetCloseHandle(hInternetConnect);
	InternetCloseHandle(hConnect);
	return 0;
}

int uConnect_to_Internet(hConnect, application_title, dwConnectionAccessRequest, dwConnectionFlags)
{
	hConnect = InternetOpen(application_title, dwConnectionAccessRequest, NULL, NULL, dwConnectionFlags);

	if (!hConnect) {
		printf("Failed to make base connection\n");
		printf("Connection Failed or Syntax error");
		DWORD WINAPI GetLastError(void);
		return 0;
	}
	else
		printf("Server Connection Successful:\t0x%x\n", hConnect);

	return hConnect;
}

int uConnect_to_Server(hConnect, hInternetConnect, website_address, dwDefaultPort, dwInternetService)
{
	hInternetConnect = InternetConnect(hConnect, website_address, dwDefaultPort, NULL, NULL, dwInternetService, 0, 0);

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

	return hInternetConnect;
}

int uConnect_to_URL(hConnect, hInternetConnect, hOpenAddress, website_address, dwAddressRequestFlags)
{
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

	return hOpenAddress;
}

int uPreform_Checks()
{
	char read[10];
	char* file_name = "test.txt";
	char* mode = "r+";
	int base_count = 0, check_success = 0, pass = 0;
	errno_t err;
	FILE *fp;

	err = fopen_s(&fp, file_name, mode);

	if (!fp)
	{
		puts("Failed to open file.");
		printf("Error:\t0x%x\n", GetLastError());
	}

	else
	{
		while (check_success != 1 && (read[base_count] = fgetc(fp)) != EOF)
		{
			if (pass > 1 && read[base_count] == "P" && read[base_count+1] == "A")
				check_success = 1;
			base_count++;
			pass++;
		}
		fclose(fp);

		if (check_success)
			puts("Success!");
		else
			puts("Failed!");

	}

	return 0;
}

int uRead_Data_from_Website(HINTERNET hOpenAddress, char DataReceived[COUNT], int DataSize, DWORD dwNumberofBytesRead)
{
	char* file_name = "test.txt";
	char* mode = "w+";
	int base_count = 0;
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, file_name, mode);

	if (!fp)
	{
		puts("Failed to open file.");
		printf("Error:\t0x%x\n", GetLastError());
	}

	else
	{
		while (InternetReadFile(hOpenAddress, DataReceived, DataSize, &dwNumberofBytesRead) && dwNumberofBytesRead)
			while (base_count < dwNumberofBytesRead)
			{
				fputc(DataReceived[base_count], fp);
				base_count++;
			}

		fclose(fp);
	}

	return 0;
}
