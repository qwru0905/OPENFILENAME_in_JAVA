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

JNIEXPORT jboolean JNICALL Java_FileManager_saveFile(JNIEnv *env, jobject obj, jstring content, jstring fileName) {
    const char *nativeContent = (*env)->GetStringUTFChars(env, content, 0);
    const char *nativeFileName = (*env)->GetStringUTFChars(env, fileName, 0);

    FILE *file = fopen(nativeFileName, "w");
    if (file == NULL) {
        return JNI_FALSE;
    }

    fprintf(file, "%s", nativeContent);
    fclose(file);

    (*env)->ReleaseStringUTFChars(env, content, nativeContent);
    (*env)->ReleaseStringUTFChars(env, fileName, nativeFileName);

    return JNI_TRUE;
}