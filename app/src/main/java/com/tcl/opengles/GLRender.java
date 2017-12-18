package com.tcl.opengles;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.tcl.opengles.jni.JNI;
import com.tcl.opengles.util.tLog;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * 项目名：   OpenGLES
 * 包名：     com.tcl.opengles
 * 文件名：   GLRender
 * 创建者：   70889
 * 创建时间： 2017/9/22 10:00
 * 描述：     TODO
 */


public class GLRender implements GLSurfaceView.Renderer {
    private static final String TAG = GLRender.class.getName();
    private Context mContext;

    public GLRender(Context context) {
        mContext = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        tLog.d(TAG, "~~~onSurfaceCreated()~~~");
        JNI.createEsJNI(mContext.getAssets(), mContext.getFilesDir().getAbsolutePath());
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        tLog.d(TAG, "~~~onSurfaceChanged()~~~");
        JNI.changeEsJNI(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        tLog.d(TAG, "~~~onDrawFrame()~~~");
        JNI.drawEsJNI();
    }

    public void onDestroy() {
        tLog.d(TAG, "~~~onDestroy()~~~");
        JNI.destoryEsJNI();
    }
}
