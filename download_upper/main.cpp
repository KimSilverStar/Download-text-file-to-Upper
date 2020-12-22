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

// ���� url_wstr���� ���� �̸� ����(~.txt)
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

// �ؽ�Ʈ ���� ������ ��� string ��ü(text), ���� ũ��(fSize)�� ���ڷ� �޾Ƽ�
// string ��ü(text)�� ������ ���� �빮�ڷ� �ٲ㼭 ����
void writeUpper(string& text, size_t fSize)
{
	for (size_t i = 0; i < fSize; i++)
		text[i] = toupper(text[i]);
}

int main()
{
	cout << "Input URL: ";
	wstring url_wstr;
	wcin >> url_wstr;	// ����ڷκ��� url �Է�
	// �Է¹��� url�� "http://"�� ���� �ȵǾ������� �տ� �߰�����
	if (url_wstr.find(L"http://") == wstring::npos)
		url_wstr = L"http://" + url_wstr;
	LPCWSTR url = url_wstr.c_str();

	wstring fname_wstr = getFileName(url_wstr);		// �Է¹��� url�κ��� ���� �̸� ����(~.txt)
	LPCWSTR fname = fname_wstr.c_str();

	DeleteUrlCacheEntry(url);
	// url�� ���� ĳ�� ���� => ���α׷� ���ึ�� ���ο� ���� �ٿ�ε�
	DWORD dwResult = URLDownloadToFile(NULL, url, fname, 0, NULL);
	if (!SUCCEEDED(dwResult)) {
		cout << "URL address is not correct" << endl;
		exit(-1);
	}

	string text;	// �ؽ�Ʈ ������ ������ ������ string ��ü
	size_t fSize;	// �ؽ�Ʈ ������ ũ��
	ifstream readFile(fname);
	if (!readFile.is_open()) {
		cout << "ifstream open() error!";
		exit(-1);
	}

	readFile.seekg(0, ios::end);
	fSize = readFile.tellg();		// �ؽ�Ʈ ������ ũ�� ����
	readFile.seekg(0, ios::beg);

	text.resize(fSize);				// string ��ü(text)�� �����̳� ũ�⸦ ���� ũ�⿡ ����
	readFile.read(&text[0], fSize);	// �ؽ�Ʈ ���� ���� string�� ����
	readFile.close();

	// text ������ �빮�ڷ� ����
	writeUpper(text, fSize);		// string ��ü(text)�� ������ ���� �빮�ڷ� �ٲ㼭 ����

	// �ٿ�ε� ���� ������ ������ ���� ���·� open
	ofstream writeFile(fname, ios::trunc);
	if (!writeFile.is_open()) {
		cout << "ofstream open() error!";
		exit(-1);
	}

	writeFile.write(text.c_str(), fSize - 1);	// �ؽ�Ʈ ���Ͽ� ���� �빮�ڷ� ����
	writeFile.close();

	return 0;
}