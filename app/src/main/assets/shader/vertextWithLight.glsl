uniform mat4 uMMatrix;
uniform mat4 uMVPMatrix;
uniform vec3 uCamera;
uniform vec3 uLightDirection;
attribute vec4 aPosition;
attribute vec4 aNormal;
attribute vec4 aColor;
varying vec4 vColor;
varying vec4 vAmbient;
varying vec4 vDiffuse;
varying vec4 vSpecular;

void directionLight(in vec4 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular, in vec3 lightDirection,
                        in vec4 lightAmbient, in vec4 lightDiffuse, in vec4 lightSpecular){
    ambient = lightAmbient;
    vec4 normalTarget = aPosition + aNormal;
    vec3 newNormal = (uMMatrix*normalTarget - uMMatrix*aPosition).xyz;
    newNormal = normalize(newNormal);
    vec3 eye = normalize(uCamera - (uMMatrix*aPosition).xyz);
    vec3 vp= normalize(lightDirection);
    vec3 halfVector = normalize(vp+eye);
    float shininess = 10.0;
    float nDotViewPosition = max(0.0, dot(newNormal, vp));
    diffuse = lightDiffuse*nDotViewPosition;
    float nDotViewHalfVector = dot(newNormal, halfVector);
    float powerFactor = max(0.0, pow(nDotViewHalfVector, shininess));
    specular = lightSpecular*powerFactor;
}

void main() {
    gl_Position = uMVPMatrix*aPosition;
    vec4 ambientTmp, diffuseTmp, specularTmp;
    directionLight(normalize(aNormal), ambientTmp, diffuseTmp, specularTmp, uLightDirection,
                        vec4(0.15, 0.15, 0.15, 1.0), vec4(0.8, 0.8, 0.8, 1.0), vec4(0.7, 0.7, 0.7, 1.0));

    vColor = aColor;
    vAmbient = ambientTmp;
    vDiffuse = diffuseTmp;
    vSpecular = specularTmp;
}
