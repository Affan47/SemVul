_mesa_PassThrough( GLfloat token )
{
   GET_CURRENT_CONTEXT(ctx);

   if (ctx->RenderMode==GL_FEEDBACK) {
      FLUSH_VERTICES(ctx, 0);
      _mesa_feedback_token( ctx, (GLfloat) (GLint) GL_PASS_THROUGH_TOKEN );
      _mesa_feedback_token( ctx, token );
   }
}
