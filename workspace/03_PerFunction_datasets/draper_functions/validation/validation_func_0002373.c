printInfo()
{
  if(GLEW_VERSION_2_0 || GLEW_ARB_shader_objects) {
    GLint bitnum = 0;
    post("glsl_fragment Hardware Info");
    post("============================");
    if(GLEW_VERSION_2_0) {
      glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &bitnum );
      post("MAX_FRAGMENT_UNIFORM_COMPONENTS: %d", bitnum);
      glGetIntegerv( GL_MAX_TEXTURE_COORDS, &bitnum );
      post("MAX_TEXTURE_COORDS: %d", bitnum);
      glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &bitnum );
      post("MAX_TEXTURE_IMAGE_UNITS: %d", bitnum);

      if(m_shader) {
        post("compiled last shader to ID: %d", m_shader);
      }
    } else {
      glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB, &bitnum );
      post("MAX_FRAGMENT_UNIFORM_COMPONENTS: %d", bitnum);
      glGetIntegerv( GL_MAX_TEXTURE_COORDS_ARB, &bitnum );
      post("MAX_TEXTURE_COORDS: %d", bitnum);
      glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &bitnum );
      post("MAX_TEXTURE_IMAGE_UNITS: %d", bitnum);

      if(m_shaderARB) {
        post("compiled last shaderARB to ID: %d", m_shaderARB);
      }
    }
  } else post("no GLSL support");
}
