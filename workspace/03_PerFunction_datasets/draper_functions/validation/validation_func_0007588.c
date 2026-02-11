valid_draw_indirect_multi(struct gl_context *ctx,
                          GLsizei primcount, GLsizei stride,
                          const char *name)
{


   if (primcount < 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "%s(primcount < 0)", name);
      return GL_FALSE;
   }


   if (stride % 4) {
      _mesa_error(ctx, GL_INVALID_VALUE, "%s(stride %% 4)", name);
      return GL_FALSE;
   }

   return GL_TRUE;
}
