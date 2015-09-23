CC=gcc

JAVA_HOME=`readlink -f /usr/bin/javac | sed "s:bin/javac::"`
LIBS=-L/opt/vc/lib/ -lEGL -lGLESv2 -lm -lc
CFLAGS=-fPIC -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I$(JAVA_HOME)/include/ -I$(JAVA_HOME)/include/linux 
OBJ = jni/util.o jni/egl.o jni/gles2.o


libJgles2.so: $(OBJ) jni/Jgles2_util.h jni/Jgles2_util.h jni/Jgles2_GLES2.h
	$(CC) -fPIC -shared -Wl,-soname,libJgles2.so $(OBJ) $(LIBS) -o $@ 

jni/util.o: jni/util.c jni/Jgles2_util.h
	$(CC) $(CFLAGS) -c $< -o $@
	
jni/egl.o: jni/egl.c jni/Jgles2_EGL.h
	$(CC) $(CFLAGS) -c $< -o $@

jni/gles2.o: jni/gles2.c jni/Jgles2_GLES2.h
	$(CC) $(CFLAGS) -c $< -o $@

jni/Jgles2_util.h: src/Jgles2/util.java
	javac -classpath src src/Jgles2/util.java
	javah -d jni -classpath src Jgles2.util
	
jni/Jgles2_EGL.h: src/Jgles2/EGL.java
	javac src/Jgles2/EGL.java
	javah -d jni -classpath src Jgles2.EGL
	
jni/Jgles2_GLES2.h: src/Jgles2/GLES2.java
	javac src/Jgles2/GLES2.java
	javah -d jni -classpath src Jgles2.GLES2
