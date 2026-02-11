_mesa_apply_stencil_transfer_ops(const struct gl_context *ctx, GLuint n,
                                 GLubyte stencil[])
{
   if (ctx->Pixel.IndexShift != 0 || ctx->Pixel.IndexOffset != 0) {
      const GLint offset = ctx->Pixel.IndexOffset;
      GLint shift = ctx->Pixel.IndexShift;
      GLuint i;
      if (shift > 0) {
         for (i = 0; i < n; i++) {
            stencil[i] = (stencil[i] << shift) + offset;
         }
      }
      else if (shift < 0) {
         shift = -shift;
         for (i = 0; i < n; i++) {
            stencil[i] = (stencil[i] >> shift) + offset;
         }
      }
      else {
         for (i = 0; i < n; i++) {
            stencil[i] = stencil[i] + offset;
         }
      }
   }
   if (ctx->Pixel.MapStencilFlag) {
      GLuint mask = ctx->PixelMaps.StoS.Size - 1;
      GLuint i;
      for (i = 0; i < n; i++) {
         stencil[i] = (GLubyte) ctx->PixelMaps.StoS.Map[ stencil[i] & mask ];
      }
   }
}
