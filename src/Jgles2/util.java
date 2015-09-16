
package Jgles2;

import java.nio.ByteOrder;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.LongBuffer;
import java.nio.FloatBuffer;

import static Jgles2.GLES2.*;

/** routines to aid use of Jgles2 mainly for native window handling
 * but a couple of simple short cut routines too */

public class util {

    static {
        System.loadLibrary("Jgles2");
    }

    // other platforms will need to translate their key values
    // into these values
    
    public static final int     KEY_ESC			=1;
    
    public static final int     KEY_ONE			=2;
    public static final int     KEY_TWO			=3;
    public static final int     KEY_THREE		=4;
    public static final int     KEY_FOUR		=5;
    public static final int     KEY_FIVE		=6;
    public static final int     KEY_SIX			=7;
    public static final int     KEY_SEVEN		=8;
    public static final int     KEY_EIGHT		=9;
    public static final int     KEY_NINE		=10;
    public static final int     KEY_ZERO		=11;
    public static final int     KEY_MINUS		=12;

    public static final int     KEY_TAB 		=15;
    public static final int     KEY_Q			=16;
    public static final int     KEY_W			=17;
    public static final int     KEY_E			=18;
    public static final int     KEY_R			=19;
    public static final int     KEY_T			=20;
    public static final int     KEY_Y			=21;
    public static final int     KEY_U			=22;
    public static final int     KEY_I			=23;
    public static final int     KEY_O			=24;
    public static final int     KEY_P			=25;
    
    public static final int     KEY_LBRACKET	=26;
    public static final int     KEY_RBRACKET	=26;
    public static final int     KEY_RETURN		=28;
    public static final int     KEY_LCTRL		=29;
    
    public static final int     KEY_A			=30;
    public static final int     KEY_S			=31;
    public static final int     KEY_D			=32;
    public static final int     KEY_F			=33;
    public static final int     KEY_G			=34;
    public static final int     KEY_H			=35;
    public static final int     KEY_J			=36;
    public static final int     KEY_K			=37;
    public static final int     KEY_L			=38;
    
    public static final int     KEY_SEMICOLON	=39;
    public static final int     KEY_APOST		=40;
    public static final int     KEY_BACKTICK	=41;
    public static final int     KEY_LSHIFT		=42;
    public static final int     KEY_HASH		=43;
    
    public static final int     KEY_Z			=44;
    public static final int     KEY_X			=45;
    public static final int     KEY_C			=46;
    public static final int     KEY_V			=47;
    public static final int     KEY_B			=48;
    public static final int     KEY_N			=49;
    public static final int     KEY_M			=50;
    
    public static final int     KEY_COMMA		=51;
    public static final int     KEY_PERIOD		=52;
    public static final int     KEY_BSLASH		=86;
    public static final int     KEY_RSHIFT		=54;
    public static final int     KEY_NUMMULT		=55;
    public static final int     KEY_LALT		=56;
    public static final int     KEY_SPACE		=57;
    public static final int     KEY_CAPS		=58;
    
    public static final int     KEY_F1			=59;
    public static final int     KEY_F2			=60;
    public static final int     KEY_F3			=61;
    public static final int     KEY_F4			=62;
    public static final int     KEY_F5			=63;
    public static final int     KEY_F6			=64;
    public static final int     KEY_F7			=65;
    public static final int     KEY_F8			=66;
    public static final int     KEY_F9			=67;
    public static final int     KEY_F10			=68;
    
    public static final int     KEY_NUMLOCK		=69;
    public static final int     KEY_SCLOCK		=70;
    public static final int     KEY_NUM7		=71;
    public static final int     KEY_NUM8		=72;
    public static final int     KEY_NUM9		=73;
    public static final int     KEY_NUMMINUS	=74;
    public static final int     KEY_NUM4		=75;
    public static final int     KEY_NUM5		=76;
    public static final int     KEY_NUM6		=77;
    public static final int     KEY_NUMPLUS		=78;
    public static final int     KEY_NUM1		=79;
    public static final int     KEY_NUM2		=80;
    public static final int     KEY_NUM3		=81;
    public static final int     KEY_NUMZERO		=82;
    public static final int     KEY_NUMPERIOD	=83;

    public static final int     KEY_FSLASH		=53;
    public static final int     KEY_F11			=87;
    public static final int     KEY_F12			=88;

    public static final int     KEY_NUMENTER	=96;
    public static final int     KEY_RCTRL		=97;
    public static final int     KEY_NUMSLASH	=98;
    public static final int     KEY_SYSRQ		=99;
    public static final int     KEY_ALTGR		=100;

    public static final int     KEY_HOME		=102;

    public static final int     KEY_PGUP		=103;

    public static final int     KEY_END			=107;

    public static final int     KEY_PGDOWN		=109;
    public static final int     KEY_INSERT		=110;
    public static final int     KEY_DELETE		=111;

    public static final int     KEY_BREAK		=119;

    public static final int     KEY_LMETA		=125;
    public static final int     KEY_RMETA		=126;
    public static final int     KEY_MENU		=127;

    public static final int     KEY_CURSL		=105;
    public static final int     KEY_CURSR		=106;
    public static final int     KEY_CURSU		=103;
    public static final int     KEY_CURSD		=108;


    
    /** creates a native window */
    public static native int make_native_window();

    
    /** capture input
     */
    public static native void captureKeyboard();
    
    /** typically once per "frame" you should run this to ensure that
     * native window events are handled and fed back to the native
     * window handler and thence to your app */
    public static native void pumpEvents();
    
    
    public static native int getWidth();
    public static native int getHeight();

	/** return the status of a particular key */
    public static native boolean keyDown(int k);
    
    /** returns the state of the mouse buttons */
    public static native int getMouseButtons();
    public static native int getMouseX();
    public static native int getMouseY();
    
    /** get a native pointer to a FloatBuffer */ 
    public static native int getFloatBufferPtr(FloatBuffer buffer);
    /** get a native pointer to a IntBuffer */ 
    public static native int getIntBufferPtr(IntBuffer buffer);
    /** get a native pointer to a ByteBuffer */ 
    public static native int getByteBufferPtr(ByteBuffer buffer);
    
    // as seen in Lwjgl (*4) - licence omitted by kind permission Brian Matzon
    /** create a direct byte buffer in native order */
	public static ByteBuffer createByteBuffer(int size) { return ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder()); }
    /** create a direct Int buffer backed by a byte buffer in native order */
	public static IntBuffer createIntBuffer(int size) { return createByteBuffer(size << 2).asIntBuffer(); }
    /** create a direct Long buffer backed by a byte buffer in native order */
	public static LongBuffer createLongBuffer(int size) { return createByteBuffer(size << 3).asLongBuffer(); }
    /** create a direct Float buffer backed by a byte buffer in native order */
	public static FloatBuffer createFloatBuffer(int size) { return createByteBuffer(size << 2).asFloatBuffer();	}
    //


	/** simply returns a handle to a shader program
	 * @param name a simple identifier to enable easy recognition of error messages
	 * @param vertShaderText the source code for the vertex shader
	 * @param fragShaderText the source code for the fragment shader */
    public static int createShaderProgram(String name, String vertShaderText, String fragShaderText) {
        int fragShader, vertShader, program=0;
        int stat;

        final IntBuffer val = ByteBuffer.allocateDirect(4).asIntBuffer(); 
               
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, fragShaderText);
        glCompileShader(fragShader);
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, val);
        if (val.get(0)==0) {
            System.out.println("Error: "+name+" fragment shader did not compile!\n");
            System.out.println("Shader log:\n"+glGetShaderInfoLog(fragShader));
            System.exit(-1);
        }
        
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, vertShaderText);
        glCompileShader(vertShader);
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, val);
        if (val.get(0)==0) {
            System.out.println("Error: "+name+" vertex shader did not compile!\n");
            System.out.println("Shader log:\n"+glGetShaderInfoLog(vertShader));
            System.exit(-1);
        }       

        program = glCreateProgram();
        glAttachShader(program, fragShader);
        glAttachShader(program, vertShader);
        glLinkProgram(program);
        
        glGetProgramiv(program, GL_LINK_STATUS, val);
        if (val.get(0)==0) {
            System.out.println("Shader log:\n"+glGetProgramInfoLog(program));
            System.exit(-1);
        }

        return program;
    }

	/** calls glGetError and returns a description of the error code
	 * @return the error description string */
    public String checkError() {
        int err = glGetError();
        String es="" ;
        if (err!=GL_NO_ERROR) {
            es = "unknown error code "+err;
            if (err==GL_INVALID_ENUM) es = "Invalid enum\n";
            if (err==GL_INVALID_VALUE) es = "invalid value\n";
            if (err==GL_INVALID_OPERATION) es = "invalid operation\n";
            if (err==GL_OUT_OF_MEMORY) es = "out of memory\n";
        }
        return es;
    }
    
    
    
       
    util() {
        System.out.println("NB do not instance me!");
    }
}
