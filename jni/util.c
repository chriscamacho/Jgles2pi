#include "Jgles2_util.h"
#include <EGL/egl.h>

#include <string.h> // memset
#include <stdbool.h>

#include <math.h>

#include "bcm_host.h"

#include <dirent.h>  // scandir
#include <string.h> // strlen
#include <fcntl.h>  // open fcntl

#include "linux/kd.h"	// keyboard stuff...
#include "termios.h"
#include "sys/ioctl.h"
#include <linux/input.h>

int __key_fd=-1; 
int __mouse_fd=-1;
// TODO when someone contributes code for other platforms
// what to do about key values? java ifdef ???
bool __keys[256];
bool __rel_mouse;
int __mouse[3]; 
int __width,__height;


JNIEXPORT jint JNICALL Java_Jgles2_util_getMouseButtons
  (JNIEnv *e, jclass c)
{
    return __mouse[2];
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getMouseX
  (JNIEnv *e, jclass c) 
{
    return __mouse[0];
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getMouseY
  (JNIEnv *e, jclass c) 
{
    return __mouse[1];
}



// as pi doesn't support (accelerated) X, only 1 fullscreen (none X) "window" is practical
static EGL_DISPMANX_WINDOW_T nativewindow;

JNIEXPORT jint JNICALL Java_Jgles2_util_make_1native_1window
				(JNIEnv *e, jclass c) {

     // create an EGL window surface
    // adapted from BCM boiler plate code    
	uint32_t screen_width;
	uint32_t screen_height;
	bcm_host_init();
	graphics_get_display_size(0 /* LCD */, &screen_width, &screen_height);

	__width=screen_width;
	__height=screen_height;  // framework globals
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;


	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
      
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = screen_width;
	dst_rect.height = screen_height;
	  
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = screen_width << 16;
	src_rect.height = screen_height << 16;        

	dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
	dispman_update = vc_dispmanx_update_start( 0 );
		 
	dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
								0/*layer*/, &dst_rect, 0/*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 
								0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
  
	nativewindow.element = dispman_element;
	nativewindow.width = screen_width;
	nativewindow.height = screen_height;
	vc_dispmanx_update_submit_sync( dispman_update );
    
    return (jint)&nativewindow;
    
}




static int __dsort (const struct dirent **a,const struct dirent **b) {
    return 1; // dummy sort
}

static int __dfilter(const struct dirent *d) {
    if (d->d_type==DT_DIR) return 0;
    int i=0;
    i=strlen(d->d_name)-1;
    //printf ("%i %c %c %c \n",d->d_type,d->d_name[i-2],d->d_name[i-1],d->d_name[i]);
    // allegedly usb keyboard symlink *always* ends kbd
    if (d->d_name[i-2]=='k'  & d->d_name[i-1]=='b'  & d->d_name[i]=='d'  ) return 1;
    return 0;
}


JNIEXPORT void JNICALL Java_Jgles2_util_captureMouse
  (JNIEnv *e, jclass c)
{
    __rel_mouse=false;


    __mouse_fd = open("/dev/input/mouse0", O_RDONLY);
    if (__mouse_fd < 0) {
        printf("opening mouse failed\n");
    } else {
        // make none blocking
        int flags = fcntl(__mouse_fd, F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(__mouse_fd, F_SETFL, flags);
    }

}

JNIEXPORT void JNICALL Java_Jgles2_util_captureKeyboard
  (JNIEnv *e, jclass c)
{

    struct dirent **eps;
    int n;

    n = scandir ("/dev/input/by-path/", &eps, __dfilter, __dsort);

    if(n >= 0 && eps != 0 && eps[0] != 0) {
        // only check 1st usb keyboard....
        char fn[256];
        sprintf(fn,"/dev/input/by-path/%s\0",eps[0]->d_name);
        __key_fd=open(fn, O_RDONLY);
        printf("using: %s\n",fn);
    }

    if (__key_fd==-1) __key_fd=0; 

    int flags;
    flags = fcntl(__key_fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(__key_fd, F_SETFL, flags);

}

JNIEXPORT void JNICALL Java_Jgles2_util_setMouseRelative
  (JNIEnv *e, jclass c, jboolean b)
{
	__rel_mouse = b;
}

JNIEXPORT void JNICALL Java_Jgles2_util_pumpEvents
  (JNIEnv *e, jclass c)
{

	if (__key_fd!=0) { 
        struct input_event ev;
        int res;
        res = read(__key_fd, &ev,sizeof(struct input_event));
        while (res>=0) {
            //printf(" %i %i %i\n",ev.type,ev.code,ev.value);
            // should probably handle MSC and SYN as well - meh
            if (ev.type==EV_KEY) {
                if (ev.value==1) {
					//printf("code down: %i\n",(ev.code & 0xff));
                    __keys[ev.code & 0xff]=true;
                } else if (ev.value==0) {
					//printf("code up: %i\n",(ev.code & 0xff));
                    __keys[ev.code & 0xff]=false;
                }
            }
            res = read(__key_fd, &ev,sizeof(struct input_event));
        }

    }
    
	if (__rel_mouse) { // if we're in relative mode
        __mouse[0]=0;  // no mouse event should = 0,0
        __mouse[1]=0;
    }
    
    if(__mouse_fd>0) {
        signed char mbuf[3];
        int mres;
        mres=read(__mouse_fd,&mbuf[0],3);
        while(mres>=0) {
            //printf("%i %i %i\n",mbuf[0]&7,mbuf[1],mbuf[2]);
            __mouse[2]=mbuf[0]&7;
            if (__rel_mouse) {
                __mouse[0]=mbuf[1];
                __mouse[1]=-mbuf[2];
            } else {
                __mouse[0]=__mouse[0]+mbuf[1];
                __mouse[1]=__mouse[1]-mbuf[2];
                if (__mouse[0]<0) __mouse[0]=0;
                if (__mouse[1]<0) __mouse[1]=0;
                if (__mouse[0]>__width) __mouse[0]=__width;
                if (__mouse[1]>__height) __mouse[1]=__height;
            }

            mres=read(__mouse_fd,&mbuf[0],3);
        }

    }
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getHeight
  (JNIEnv *e, jclass c)
{
    return __height;
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getWidth
  (JNIEnv *e, jclass c)
{
    return __width;
}

JNIEXPORT jboolean JNICALL Java_Jgles2_util_keyDown
  (JNIEnv *e, jclass c, jint k)
{
    return __keys[k];
}


// these are identical but are needed so that they can be
// called from java with different types of buffer.
JNIEXPORT jint JNICALL Java_Jgles2_util_getFloatBufferPtr
  (JNIEnv *e, jclass c, jobject buff)
{
	void* ptr = (void*)(*e)->GetDirectBufferAddress(e, buff);
	return (jint)ptr;
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getIntBufferPtr
  (JNIEnv *e, jclass c, jobject buff)
{
	void* ptr = (void*)(*e)->GetDirectBufferAddress(e, buff);
	return (jint)ptr;
}

JNIEXPORT jint JNICALL Java_Jgles2_util_getByteBufferPtr
  (JNIEnv *e, jclass c, jobject buff)
{
	void* ptr = (void*)(*e)->GetDirectBufferAddress(e, buff);
	return (jint)ptr;
}
