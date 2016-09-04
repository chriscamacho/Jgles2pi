This is a one off conversion I did for the PI as I don't have a PI anymore I don't maintain it
for more upto date code use https://github.com/chriscamacho/Jgles2 which should be easily 
modified to work on the PI

Jgles2pi
------


How is Jgles2 organised ?
-------------------------

There are just three classes

Jgles2.EGL     access to libEGL

Jgles2.GLES2   access to libGLES v2.0

Jgles2.util    some platform specific stuff, general utilities etc.

There used to be a C math library wrapped as well, but there was little
to be gained from this and there are various Math routines - matrix, 
quaternion as java versions in the example (test folder) 


Is it just like using GLES ?
----------------------------

Its close but there are a few slight differences for convenience



So is it ready to rock and roll ?
---------------------------------

Basically yes - there are a small handful of routines unwrapped that
I don't use (contributions welcome) There is a full application
demonstrating gimbaless rotation, the library has also been tested using
techniques like render to texture.





I'd like to chat to talk about how I might help?
------------------------------------------------

my email account is codifies with a co uk domain of bedroomcoders, what will we do when
spam bots can work that one out...
 
