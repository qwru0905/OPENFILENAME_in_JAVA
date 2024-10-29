# OPENFILENAME IN JAVA
This code can open Windows file open ui in java.

Now selected language is English.
[**English**](readme.md)

## How?
This guide is based on Java 22, Windows 11 64-bit and IntelliJ.   
I think it also works in Java 17~21, Windows 10 64bit.
1. Go [here](https://github.com/niXman/mingw-builds-binaries/releases) and download x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0.7z
2. Unzip the file
3. Place the folder named mingw64 in the folder you unzipped into C:\Program Files
4. Add the `C:\Program Files\mingw64\bin` to your computer's PATH environment variable
5. Add new project in Intellij
6. Add new java file
7. Write the following code inside the java file:
```java
public class FileManager {
    static {
        try {
            System.loadLibrary("filemanager");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
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
8. Open CMD
(**DO NOT OPEN INTELLIJ'S CMD, THIS WILL NOT RECOGNIZE THE ENVIRONMENT VARIABLE**)
and change the working directory of cmd to '(project location)\src'
9. Write the following code in cmd:
`javac -h native FileManager.java`
10. Create a file named filemanager.c inside the native directory and write the following code:
```C
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
11. Write the following code in cmd:
`gcc -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o filemanager.dll native/filemanager.c -lole32 -luuid -lcomdlg32`
12. In IntelliJ IDEA, go to 'File' > 'Project Structure.'
13. Select 'Libraries' and click '+' to add a 'Java' library.
14. Choose the directory where the compiled shared library file (filemanager.dll) is located.
15. Then, you can open Windows file open ui.