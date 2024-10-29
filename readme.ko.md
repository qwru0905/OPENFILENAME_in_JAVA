# JAVA에서의 OPENFILENAME
이 코드는 자바에서 윈도우 파일 오픈 ui를 열 수 있습니다.

Now selected language is Korean.   
[English](readme.md), [**Korean**](readme.ko.md)

## 하는 방법
이 가이드는 자바 22 버전, 윈도우 11 64비트, 그리고 IntelliJ 기준으로 작성되어 있습니다.   
아마도 자바 17~21 버전, 윈도우 10 64비트에서도 실행이 될 수 있을 것입니다.
1. [여기](https://github.com/niXman/mingw-builds-binaries/releases)로 간 뒤 x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0.7z 를 다운받으세요.
2. 그 파일의 압축을 푸세요.
3. 당신이 압축을 푼 파일 안에 이름이 mingw64인 폴더를 C:\Program Files로 옮기세요.
4. 당신의 환경 변수 PATH에 `C:\Prpgram Files\mingw62\bin`을 추가하세요.
5. Intellij에서 새로운 프로젝트를 만들세요.
6. 새로운 자바 파일을 만들세요.
7. 자바 파일 안에 코드를 다음과 같이 적으세요:
```java copy
public class FileManager {
    static {
        try {
            System.loadLibrary("filemanager");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("네이티브 라이브러리를 로드하는데 실패하였습니다: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public native String selectFile();

    public static void main(String[] args) {
        FileManager fm = new FileManager();
        String selectedFile = fm.selectFile();
        System.out.println("Selected file: " + selectedFile);
    }
}
```
8. CMD를 열고
(**INTELLIJ의 CMD를 열지마세요. 그렇지 않으면 환경변수를 인식하지 못할 것입니다.**)
cmd의 작업 위치를 '(프로젝트 위치)\src'로 바꾸세요.
9. cmd에서 다음과 같은 코드를 쓰세요:
`javac -h native FileManager.java`
10. native 디렉토리에서 이름이 filemanager.c인 파일을 만들고 다음과 같이 코드를 작성하세요:
```C copy
#include <jni.h>
#include <windows.h>
#include <stdio.h>
#include "FileManager.h"

JNIEXPORT jstring JNICALL Java_FileManager_selectFile(JNIEnv *env, jobject obj) {
    OPENFILENAME ofn;
    char szFile[260] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        return (*env)->NewStringUTF(env, szFile);
    } else {
        return NULL;
    }
}
```
11. cmd에서 다음과 같은 코드를 쓰세요:
`gcc -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o filemanager.dll native/filemanager.c -lole32 -luuid -lcomdlg32`
12. IntelliJ에서, 'File' > 'Project Structure.'로 이동합니다.
13. 'Libraries'를 선택하고 '+'를 클릭하여 'Java' 라이브러리를 추가합니다.
14. 컴파일된 공유 라이브러리 파일(filemanager.dll)이 있는 디렉토리를 선택합니다.
15. 그러면, 당신은 윈도우 파일 오픈 ui를 열 수 있습니다.
