OF_GLSL_SHADER_HEADER

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec2 random2(vec2 p) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main() {
    vec2 st = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    vec2 st0 = st;
    vec3 color = vec3(.0);

    /*
    if (u_time < 9.0) {
        st *= 100. - u_time * 10.0;
    } else {
        st *= 100. - u_time;
    }
    */
    st *= exp(-u_time*0.3 + 5.0);
    // Scale

    // Tile the space
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);

    float m_dist = 1.0;  // minimum distance

    for (int y= -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            // Neighbor place in the grid
            vec2 neighbor = vec2(float(x),float(y));

            // Random position from current + neighbor place in the grid
            vec2 point = random2(i_st + neighbor);

			// Animate the point
            point = 0.5 + 0.5*sin(u_time*0.3 + 6.2831*point);

			// Vector between the pixel and the point
            vec2 diff = neighbor + point - f_st;

            // Distance to the point
            float dist = length(diff);

            // Keep the closer distance
            m_dist = min(m_dist, dist);
        }
    }

    // Draw the min distance (distance field)
    m_dist = m_dist * exp(-length(st0));
    color += (0.07 / m_dist) * vec3(0.9, 0.13, 0.0);

    // Draw cell center
    // color += 1.-step(.02, m_dist);

    // Draw grid
    // color.r += step(.98, f_st.x) + step(.98, f_st.y);

    // Show isolines
    // color -= step(.7,abs(sin(27.0*m_dist)))*.5;

    gl_FragColor = vec4(color,1.0);
}
