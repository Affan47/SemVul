gst_opengl_glLightModelv (GLenum pname, OOP paramsOOP)
{
  GLfloat *params;
  int size = gst_opengl_glLightModelv_size (pname);
  if (size == 0)
    return GL_INVALID_ENUM;

  params = (GLfloat *) alloca (sizeof (GLfloat) * size);
  params = gst_opengl_oop_to_array (params, paramsOOP, size);
  if (!params)
    return GL_INVALID_VALUE;

  glLightModelfv (pname, params);
  return 0;
}
