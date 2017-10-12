#version 200 es
precision mediump float;
uniform sampler2D sTexture;
varying vec2 vTextureCoord;

void main() {
    gl_FragColor = texture(sTexture, vTextureCoord);
}
