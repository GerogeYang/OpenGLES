precision mediump float;
varying vec4 vColor;
varying vec4 vAmbient;
varying vec4 vDiffuse;
varying vec4 vSpecular;

void main() {
    gl_FragColor = vColor*vAmbient+vColor*vDiffuse+vColor*vSpecular;
}