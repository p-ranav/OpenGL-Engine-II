#version 450 core

in vec4 v2f_position_w;
in vec4 v2f_normal_w;
in vec2 v2f_texture_coordinates;

// Light Properties
uniform vec4 eye_position_w;
uniform vec4 light_position_w;
uniform vec4 light_color;

// Material Properties
uniform vec4 material_emissive;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform float material_shininess;

// Global Ambient contribution
uniform vec4 ambient; 

// Texture for Earth
uniform sampler2D earth_texture;

layout (location=0) out vec4 out_color;

void main() {
    // Compute the emissive term.
    vec4 emissive = material_emissive;

    // Compute the diffuse term.
    vec4 N = normalize(v2f_normal_w);
    vec4 L = normalize(light_position_w - v2f_position_w);
    float NdotL = max(dot(N, L), 0);
    vec4 diffuse =  NdotL * light_color * material_diffuse;
    
    out_color = (emissive + ambient + diffuse) * texture(earth_texture, v2f_texture_coordinates);
}