evgl_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
   Render_Engine_GL_Context *ctx = current_evgl_ctx;
   int rot = 0;
   int oc[4], nc[4];

   if ((gl_direct_img_obj) && (gl_direct_enabled) && (ctx) && (!ctx->current_fbo))
     {
        if ((current_engine) && (current_engine->win) && (current_engine->win->gl_context))
           rot = current_engine->win->gl_context->rot;
        else
           ERR("Unable to retrieve rotation angle: %d", rot);

        compute_gl_coordinates(gl_direct_img_obj, rot, 1, x, y, width, height, oc, nc);
        glReadPixels(nc[0], nc[1], nc[2], nc[3], format, type, pixels);
     }
   else
      glReadPixels(x, y, width, height, format, type, pixels);
}
