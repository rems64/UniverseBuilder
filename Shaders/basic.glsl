//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex;

out vec3 col;

uniform vec3 u_color;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(vertex.x, vertex.y, vertex.z, 1.0);
    col = vec3((vertex.x+1)/2*u_color.x, (vertex.y+1)/2*u_color.y, (vertex.z+1)/2*u_color.z);
};

//shader fragment
#version 330 core
in vec3 col;
out vec4 color;

void main()
{    
    color = vec4(col.r, col.g, col.b, 1.0);
}