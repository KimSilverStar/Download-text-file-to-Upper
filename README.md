# HW5 - 코딩 과제 1번

## 영문 웹문서 다운로드 프로그램

---

## 사용 방법

- "Input URL: " 프롬프트에 다운로드 받을 url 웹 문서를 입력하시면 됩니다.
- url을 잘못 입력하면 "URL address is not correct" 라는 메시지를 출력하고,
  프로그램을 종료합니다.
- 다운로드하여 저장되는 웹 문서(.txt 형식의 텍스트 파일)는 프로그램 실행 파일
  (download_upper.exe)과 같은 경로에 저장이 됩니다.

## 구현 내용 및 방법

- Language: C++
- IDE: Visual Studio 2019
- Library: urlmon.lib, Wininet.lib

1. 입력받은 url에서 저장할 파일 이름 추출(~.txt의 형식)
2. ifstream을 사용하여 다운로드 받은 파일의 크기(byte)를 알아내고,
   이를 토대로 파일 전체 내용을 읽어서 string 컨테이너에 저장
3. 원본 파일의 내용이 저장된 string 컨테이너에서 toupper() 함수를 사용하여 대문자로 바꿔서 저장
4. ofstream을 사용하여 다운로드 받은 원본 파일의 기존 내용을 지우고,
   문서 내용을 대문자로 저장한 string 컨테이너로 기록
