is_depth_texture(const struct gl_texture_object *tObj)
{
   GLenum format = tObj->Image[0][tObj->BaseLevel]->_BaseFormat;
   return format == GL_DEPTH_COMPONENT || format == GL_DEPTH_STENCIL_EXT;
}
