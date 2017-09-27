package com.tcl.opengles.util;

import android.util.Log;

/**
 * 项目名：   OpenGLES
 * 包名：     com.tcl.opengles.util
 * 文件名：   tLog
 * 创建者：   70889
 * 创建时间： 2017/9/22 10:09
 * 描述：     TODO
 */


public class tLog {
    private static final String TAG = "OpenGLES-Java-Debug-";
    private static boolean mDebug = true;

    public static void setDebug(boolean debug) {
        mDebug = debug;
    }

    public static void v(String tag, String msg) {
        if (mDebug) {
            Log.v(TAG + tag, msg);
        }
    }

    public static void d(String tag, String msg) {
        if (mDebug) {
            Log.d(TAG + tag, msg);
        }
    }

    public static void i(String tag, String msg) {
        if (mDebug) {
            Log.i(TAG + tag, msg);
        }
    }

    public static void w(String tag, String msg) {
        if (mDebug) {
            Log.w(TAG + tag, msg);
        }
    }

    public static void e(String tag, String msg) {
        if (mDebug) {
            Log.e(TAG + tag, msg);
        }
    }
}
