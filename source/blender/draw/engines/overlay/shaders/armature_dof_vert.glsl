
/* ---- Instantiated Attrs ---- */
in vec2 pos;

/* ---- Per instance Attrs ---- */
/* Assumed to be in world coordinate already. */
in vec4 color;
in mat4 inst_obmat;

flat out vec4 finalColor;

vec3 sphere_project(float ax, float az)
{
  float sine = 1.0 - ax * ax - az * az;
  float q3 = sqrt(max(0.0, sine));

  return vec3(-az * q3, 0.5 - sine, ax * q3) * 2.0;
}

void main()
{
  mat4 model_mat = inst_obmat;
  model_mat[0][3] = model_mat[1][3] = model_mat[2][3] = 0.0;
  model_mat[3][3] = 1.0;

  vec2 amin = vec2(inst_obmat[0][3], inst_obmat[1][3]);
  vec2 amax = vec2(inst_obmat[2][3], inst_obmat[3][3]);

  vec3 final_pos = sphere_project(pos.x * abs((pos.x > 0.0) ? amax.x : amin.x),
                                  pos.y * abs((pos.y > 0.0) ? amax.y : amin.y));
  gl_Position = ViewProjectionMatrix * (model_mat * vec4(final_pos, 1.0));
  finalColor = color;
}