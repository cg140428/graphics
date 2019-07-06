#version 120                  // GLSL 1.20

uniform mat4 u_normal_matrix;

uniform vec3 u_cam_verctor_vc;
uniform vec3 u_light_vector_vc;
uniform vec4 u_light_diffuse;
uniform vec4 u_material_diffuse;

uniform vec4 u_light_ambient;
uniform vec4 u_material_ambient;

uniform vec4  u_light_specular;
uniform vec4  u_material_specular;

uniform float u_material_shininess;

varying vec3 v_color;         // per-fragment color (per-fragment input)
varying vec3 v_vertex_vc;
varying vec3 v_normal_vc;

vec3 calc_color()
{
  vec3 color = vec3(0);

  vec3 p_wc = normalize((u_normal_matrix * vec4(v_vertex_vc, 1)).xyz);//
  vec3 n_wc = normalize((u_normal_matrix * vec4(v_normal_vc, 0)).xyz);//
  vec3 l_wc = normalize(u_light_vector_vc - p_wc);//

  vec3 r_wc = reflect(-l_wc,n_wc);//
  vec3 v_wc = normalize(u_cam_verctor_vc - p_wc);//
  color += (u_light_ambient * u_material_ambient).xyz;

  float ndotl = max(0,dot(n_wc, l_wc));
  color += (ndotl * u_light_diffuse * u_material_diffuse).xyz;
  
  float rodtv = max(0, dot(r_wc,v_wc));
  color += (pow(rodtv, u_material_shininess) * u_light_specular * u_material_specular).xyz;

  return color;
}

void main()
{
	//gl_FragColor = vec4(v_color, 1.0f);
	vec3 color = calc_color();
	gl_FragColor = vec4(color,1.0f);
}