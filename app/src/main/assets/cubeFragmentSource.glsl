precision mediump float;
varying vec4 vColor;
varying vec4 vAmbient;
void main() {
    gl_FragColor = vColor*vAmbient;
}