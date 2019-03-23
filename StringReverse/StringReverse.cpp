// StringReverse.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>

BOOL StringReverseW(PWSTR pWideCharStr) {
	PWSTR pEndOfStr = pWideCharStr + wcslen(pWideCharStr) - 1;
	wchar_t cCharT;
	while (pWideCharStr < pEndOfStr) {
		cCharT = *pWideCharStr;
		*pWideCharStr = *pEndOfStr;
		*pEndOfStr = cCharT;
		pWideCharStr++;
		pEndOfStr--;
	}

	return(TRUE);
}

BOOL StringReverseA(PSTR pMultiByteStr) {
	PWSTR pWideCharStr;
	int nLenOfWideCharStr;
	BOOL fOk = FALSE;

	nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, -1, NULL, 0);
	pWideCharStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0, nLenOfWideCharStr * sizeof(WCHAR));

	if (pWideCharStr == NULL) {
		return(fOk);
	}

	MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, -1, pWideCharStr, nLenOfWideCharStr);
	fOk = StringReverseW(pWideCharStr);

	if (fOk) {
		WideCharToMultiByte(CP_ACP, 0, pWideCharStr, -1, pMultiByteStr, strlen(pMultiByteStr), NULL, NULL);
	}

	HeapFree(GetProcessHeap(), 0, pWideCharStr);

	return(fOk);
}

int main()
{
	wchar_t wc[] = L"abcde";
	char c[] = "abcde";

	StringReverseW(wc);
	StringReverseA(c);

	std::wcout << wc;
	std::cout << "\n";
	std::cout << c;
}