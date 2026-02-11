openMessGL2(void)
{
  if (m_shader) {
    glDeleteShader( m_shader );
    gem::utils::glsl::delshader(m_shader);
  }
  m_shader = glCreateShader(m_shaderTarget);

  if (!m_shader)
    {
      error("could not create GLSL shader object");
      return false;
    }
  const char * vs = m_shaderString;
  glShaderSource( m_shader, 1, &vs, NULL );
  glCompileShader( m_shader );
  glGetShaderiv( m_shader, GL_COMPILE_STATUS, &m_compiled );
  if (!m_compiled) {
    GLint	length;
    GLchar* log;
    glGetShaderiv( m_shader, GL_INFO_LOG_LENGTH, &length );
    log = (GLchar*)malloc( length * sizeof(GLchar) );
    glGetShaderInfoLog( m_shader, length, NULL, log );
    post("compile Info_log:");
    post("%s", log );
    error("shader not loaded");
    free(log);
    return false;
  }
  return true;
}
