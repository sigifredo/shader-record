OF_GLSL_SHADER_HEADER


#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

void main()
{
    vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);

    gl_FragColor = vec4(uv.xyy, 1.0);
}