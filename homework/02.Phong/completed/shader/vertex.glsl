#version 120                  // GLSL 1.20

uniform mat4 u_pvm_matrix;
uniform mat4 u_vm_matrix;
uniform mat4 u_normal_matrix;

attribute vec3 a_vertex;
attribute vec3 a_normal;

varying vec3 v_color;       // per-vertex color (per-vertex output)
varying vec3 v_vertex_vc;
varying vec3 v_normal_vc;

uniform vec3 u_light_vector_vc;
uniform vec4 u_light_diffuse;
uniform vec4 u_material_diffuse;

vec3 calc_color()
{
  vec3 color = vec3(0);

  vec3 p_wc = normalize(u_normal_matrix * vec4(a_vertex, 1)).xyz;
  vec3 n_wc = normalize(u_normal_matrix * vec4(a_normal, 0)).xyz;
  vec3 l_wc = normalize(u_light_vector_vc - p_wc);

  float ndotl = max(0,dot(n_wc, l_wc));
  color += (ndotl * u_light_diffuse * u_material_diffuse).xyz;

  return color;
}

void main() 
{
  //v_normal_vc = (normalize(u_normal_matrix * vec4(a_normal,0.0f))).xyz;
  //v_vertex_vc = (u_vm_matrix * vec4(a_vertex, 1.0f)).xyz;
  v_vertex_vc = a_vertex;
  v_normal_vc = a_normal;
  v_color = calc_color();

  gl_Position = u_pvm_matrix * vec4(a_vertex, 1);
}