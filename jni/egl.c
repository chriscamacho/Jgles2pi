#include "Jgles2_util.h"
#include <EGL/egl.h>

JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglSwapInterval
  (JNIEnv *e, jclass c, jint d, jint i)
{
    return eglSwapInterval((EGLDisplay)d,i);
}

JNIEXPORT jint JNICALL Java_Jgles2_EGL_eglGetDisplay
                                (JNIEnv *e, jclass c, jint d) 
{
    return (jint)eglGetDisplay((NativeDisplayType)(int)d);
}

JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglInitialize
                                (JNIEnv *e, jclass c, jint d ) 
{
    return (jboolean)eglInitialize((EGLDisplay)(int)d,NULL,NULL);
}


JNIEXPORT jstring JNICALL Java_Jgles2_EGL_eglQueryString
                                (JNIEnv *e, jclass c, jint d, jint n) 
{
    char const* QueryString;
    QueryString = eglQueryString((EGLDisplay)(int)d, (EGLint)n);
    return (*e)->NewStringUTF(e, QueryString); 
}

JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglChooseConfig
  (JNIEnv *env, jclass c, jint display, jobject jattribs, jobject jconfigs, jint size, jobject jnum)
{
    int num=0;
    EGLint const* attribs = (EGLint const*)(*env)->GetDirectBufferAddress(env, jattribs);
    void* configs = (void*)(*env)->GetDirectBufferAddress(env, jconfigs);
    
    int r = eglChooseConfig((EGLDisplay)(int)display,attribs,configs,size,&num);
    EGLint* ret = (EGLint*)((*env)->GetDirectBufferAddress(env, jnum));
    ret[0] = num;
   
    return r;
}

JNIEXPORT jint JNICALL Java_Jgles2_EGL_eglCreateContext
        (JNIEnv *env, jclass c, jint disp, jint conf, jint share, jobject jattrib) 
{
    EGLint const* attribs = (EGLint const*)(*env)->GetDirectBufferAddress(env, jattrib);
    return (jint)eglCreateContext((EGLDisplay)(int)disp, (EGLConfig)conf, (EGLContext)share, attribs);
}

JNIEXPORT jint JNICALL Java_Jgles2_EGL_eglQueryContext
        (JNIEnv *env, jclass c, jint disp, jint ctx, jint atrib, jobject val) 
{
    int v=0;
    int r=eglQueryContext((EGLDisplay)(int)disp,(EGLContext)ctx, atrib, &v);
    EGLint* ret = (EGLint*)((*env)->GetDirectBufferAddress(env, val));
    ret[0] = v;

    return r;
}



JNIEXPORT jint JNICALL Java_Jgles2_EGL_eglCreateWindowSurface
  (JNIEnv *env, jclass c, jint jdisp, jint jconf, jint jwin, jobject jattribs)
{
    EGLint* attribs = 0;
    if (jattribs!=0) attribs = (EGLint*)(*env)->GetDirectBufferAddress(env, jattribs);
    
	return (jint)eglCreateWindowSurface((EGLDisplay)(int)jdisp,(EGLConfig)jconf,(NativeWindowType*)jwin,NULL);

}

JNIEXPORT void JNICALL Java_Jgles2_EGL_eglQuerySurface
  (JNIEnv *env, jclass c, jint disp, jint surf, jint atrib, jobject val)
{
    int v=0;
    eglQuerySurface((EGLDisplay)(int)disp,(EGLSurface)surf,atrib,&v);
    EGLint* ret = (EGLint*)((*env)->GetDirectBufferAddress(env, val));
    ret[0] = v;    
}

JNIEXPORT void JNICALL Java_Jgles2_EGL_eglGetConfigAttrib
  (JNIEnv *env, jclass c, jint disp, jint conf, jint atrib, jobject val)
{
    int v=0;
    eglGetConfigAttrib((EGLDisplay)(int)disp, (EGLConfig)conf, atrib, &v);
    EGLint* ret = (EGLint*)((*env)->GetDirectBufferAddress(env, val));
    ret[0] = v;    
}

JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglMakeCurrent
  (JNIEnv *e, jclass c, jint disp, jint draw, jint read, jint context)
{
    return eglMakeCurrent((EGLDisplay)disp, (EGLSurface)draw, (EGLSurface)read, (EGLContext)context);
}

JNIEXPORT jint JNICALL Java_Jgles2_EGL_eglGetError
  (JNIEnv *e, jclass c)
{
    return eglGetError();
}

JNIEXPORT void JNICALL Java_Jgles2_EGL_eglSwapBuffers
  (JNIEnv *e, jclass c, jint disp, jint surf)
{
    eglSwapBuffers((EGLDisplay)disp,(EGLSurface)surf);
}

JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglDestroySurface
  (JNIEnv *e, jclass c, jint d, jint s)
{
    eglDestroySurface((EGLDisplay)d, (EGLSurface)s);
}  
  
JNIEXPORT jboolean JNICALL Java_Jgles2_EGL_eglDestroyContext
  (JNIEnv *e, jclass c, jint d, jint ctx)
{
    eglDestroyContext((EGLDisplay)d, (EGLContext)ctx);  
}
