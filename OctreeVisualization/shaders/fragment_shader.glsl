#version 120

// Note: GLSL 1.20 does not support the `out` qualifier for fragment color.
void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); // Output fragment color: white
}
