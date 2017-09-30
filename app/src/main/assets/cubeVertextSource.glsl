attribute vec4 vPosition;
uniform mat4 vMatrix;
varying vec4 vColor;
attribute vec4 aColor;
varying vec4 vAmbient;
attribute vec4 aAmbient;
void main() {
    gl_Position = vMatrix*vPosition;
    vColor = aColor;
    vAmbient = aAmbient;
}
