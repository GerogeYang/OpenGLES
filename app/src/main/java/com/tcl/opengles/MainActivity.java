package com.tcl.opengles;

import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

import com.tcl.opengles.util.tLog;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getName();

    private GLSurfaceView mGLSurfaceView;
    private GLRender mGLRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        mGLSurfaceView = new GLSurfaceView(this);

        mGLSurfaceView.setEGLContextClientVersion(2);
        mGLSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        mGLSurfaceView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        mGLSurfaceView.setZOrderOnTop(true);


        mGLRender = new GLRender(this);
        mGLSurfaceView.setRenderer(mGLRender);
        setContentView(mGLSurfaceView);
        tLog.d(TAG, "~~~onCreate()~~~");
    }

    @Override
    protected void onResume() {
        tLog.d(TAG, "~~~onResume()~~~");
        super.onResume();
        mGLSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        tLog.d(TAG, "~~~onPause()~~~");
        super.onPause();
        mGLSurfaceView.onPause();
    }

    @Override
    protected void onDestroy() {
        tLog.d(TAG, "~~~onDestroy()~~~");
        super.onDestroy();
        mGLRender.onDestroy();
    }
}
