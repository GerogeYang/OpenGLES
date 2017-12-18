package com.tcl.opengles.jni;

import android.content.res.AssetManager;

/**
 * 项目名：   OpenGLES
 * 包名：     com.tcl.opengles.jni
 * 文件名：   JNI
 * 创建者：   70889
 * 创建时间： 2017/9/22 10:28
 * 描述：     TODO
 */


public class JNI {
    static {
        System.loadLibrary("native-lib");
    }

    public native static void createEsJNI(AssetManager assetManager, String pathToInternalDir);

    public native static void changeEsJNI(int width, int height);

    public native static void drawEsJNI();

    public native static void destoryEsJNI();
}
