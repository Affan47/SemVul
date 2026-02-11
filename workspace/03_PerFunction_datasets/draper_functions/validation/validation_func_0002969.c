r200RenderMode( struct gl_context *ctx, GLenum mode )
{
   r200ContextPtr rmesa = R200_CONTEXT(ctx);
   FALLBACK( rmesa, R200_FALLBACK_RENDER_MODE, (mode != GL_RENDER) );
}
