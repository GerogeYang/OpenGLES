uniform mat4 uMVPMatrix;
varying vec4 uColor;
attribute vec4 aPosition;
attribute vec4 aColor;
void main() {
    gl_Position = uMVPMatrix*aPosition;
    uColor = aColor;
}