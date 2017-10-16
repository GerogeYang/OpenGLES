precision mediump float;
uniform sampler2D sTexture;
varying vec2 vTextureCoord;
varying vec4 vColor;
varying vec4 vAmbient;
varying vec4 vDiffuse;
varying vec4 vSpecular;

void main() {
    vec4 finalColor = texture2D(sTexture, vTextureCoord);
    gl_FragColor = finalColor*vAmbient+finalColor*vDiffuse+finalColor*vSpecular;
}
