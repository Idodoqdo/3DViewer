#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec4 lines_color;
uniform vec4 ver_color;

void main()
{
    gl_FragColor = lines_color;
}
