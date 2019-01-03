#version 330 core

in vec2 TexCoords;

uniform sampler2D layer_0;
uniform sampler2D layer_1;
uniform sampler2D layer_2;
uniform sampler2D layer_3;
uniform sampler2D layer_4;
uniform sampler2D layer_5;
uniform sampler2D layer_6;
uniform float offset;

void main() {
    vec2 layer_0_coords = TexCoords;
    vec2 layer_1_coords = TexCoords;
    vec2 layer_2_coords = TexCoords;
    vec2 layer_3_coords = TexCoords;
    vec2 layer_4_coords = TexCoords;
    vec2 layer_5_coords = vec2(TexCoords.s + offset, TexCoords.t);
    vec2 layer_6_coords = TexCoords;

    vec4 texel_0 = texture2D(layer_0, layer_0_coords);
    vec4 texel_1 = texture2D(layer_1, layer_1_coords);
    vec4 texel_2 = texture2D(layer_2, layer_2_coords);
    vec4 texel_3 = texture2D(layer_3, layer_3_coords);
    vec4 texel_4 = texture2D(layer_4, layer_4_coords);
    vec4 texel_5 = texture2D(layer_5, layer_5_coords);
    vec4 texel_6 = texture2D(layer_6, layer_6_coords);

    // start from the last layer
    gl_FragColor = texel_6;
    gl_FragColor = vec4(texel_5.a) * texel_5 + vec4(1.0 - texel_5.a) * gl_FragColor;
    gl_FragColor = vec4(texel_4.a) * texel_4 + vec4(1.0 - texel_4.a) * gl_FragColor;
    gl_FragColor = vec4(texel_3.a) * texel_3 + vec4(1.0 - texel_3.a) * gl_FragColor;
    gl_FragColor = vec4(texel_2.a) * texel_2 + vec4(1.0 - texel_2.a) * gl_FragColor;
    gl_FragColor = vec4(texel_1.a) * texel_1 + vec4(1.0 - texel_1.a) * gl_FragColor;
    gl_FragColor = vec4(texel_0.a) * texel_0 + vec4(1.0 - texel_0.a) * gl_FragColor;
}
