#version 420 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 TestViewDir;
in vec2 TexCoords;
in mat3 TBN;
  
uniform vec3 camPos;
  
uniform vec3  albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

 struct Material {
    sampler2D normalMap;
    sampler2D albedo;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ambientOcc;
};  

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool UI;
    bool active;
};  

void main(){

    vec3 norm = texture(material.normalMap,TexCoords).rgb;
    norm = normalize(norm*2.0-1.0);
    norm = normalize(TBN*norm);
   

}