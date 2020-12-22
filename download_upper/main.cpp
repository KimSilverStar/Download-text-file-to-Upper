#include <iostream>
#include <fstream>
#include <cstdlib>
#include <urlmon.h>
#include <Wininet.h>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cctype>
#pragma comment(lib, "urlmon.lib")
#pragma comment (lib, "Wininet.lib")
using namespace std;

// 인자 url_wstr에서 파일 이름 추출(~.txt)
wstring getFileName(const wstring& url_wstr)
{
	size_t i = url_wstr.find(L".txt");
	while (true) {
		if (url_wstr[i] == L'/')
			break;
		i--;
	}
	i++;

	wstring fname_wstr;
	while (true) {
		fname_wstr += url_wstr[i];
		i++;
		if (url_wstr[i] == NULL)
			break;
	}

	return fname_wstr;
}

// 텍스트 파일 내용이 담긴 string 객체(text), 파일 크기(fSize)를 인자로 받아서
// string 객체(text)의 내용을 영문 대문자로 바꿔서 저장
void writeUpper(string& text, size_t fSize)
{
	for (size_t i = 0; i < fSize; i++)
		text[i] = toupper(text[i]);
}

int main()
{
	cout << "Input URL: ";
	wstring url_wstr;
	wcin >> url_wstr;	// 사용자로부터 url 입력
	// 입력받은 url에 "http://"가 포함 안되어있으면 앞에 추가해줌
	if (url_wstr.find(L"http://") == wstring::npos)
		url_wstr = L"http://" + url_wstr;
	LPCWSTR url = url_wstr.c_str();

	wstring fname_wstr = getFileName(url_wstr);		// 입력받은 url로부터 파일 이름 추출(~.txt)
	LPCWSTR fname = fname_wstr.c_str();

	DeleteUrlCacheEntry(url);
	// url에 대한 캐시 삭제 => 프로그램 실행마다 새로운 파일 다운로드
	DWORD dwResult = URLDownloadToFile(NULL, url, fname, 0, NULL);
	if (!SUCCEEDED(dwResult)) {
		cout << "URL address is not correct" << endl;
		exit(-1);
	}

	string text;	// 텍스트 파일의 내용을 저장할 string 객체
	size_t fSize;	// 텍스트 파일의 크기
	ifstream readFile(fname);
	if (!readFile.is_open()) {
		cout << "ifstream open() error!";
		exit(-1);
	}

	readFile.seekg(0, ios::end);
	fSize = readFile.tellg();		// 텍스트 파일의 크기 저장
	readFile.seekg(0, ios::beg);

	text.resize(fSize);				// string 객체(text)의 컨테이너 크기를 파일 크기에 맞춤
	readFile.read(&text[0], fSize);	// 텍스트 파일 내용 string에 저장
	readFile.close();

	// text 내용을 대문자로 저장
	writeUpper(text, fSize);		// string 객체(text)의 내용을 영문 대문자로 바꿔서 저장

	// 다운로드 받은 파일의 내용을 지운 상태로 open
	ofstream writeFile(fname, ios::trunc);
	if (!writeFile.is_open()) {
		cout << "ofstream open() error!";
		exit(-1);
	}

	writeFile.write(text.c_str(), fSize - 1);	// 텍스트 파일에 영문 대문자로 저장
	writeFile.close();

	return 0;
}