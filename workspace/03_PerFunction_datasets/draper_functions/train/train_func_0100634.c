save_ProgramStringARB(GLenum target, GLenum format, GLsizei len,
                      const GLvoid * string)
{
   GET_CURRENT_CONTEXT(ctx);
   Node *n;

   ASSERT_OUTSIDE_SAVE_BEGIN_END_AND_FLUSH(ctx);

   n = alloc_instruction(ctx, OPCODE_PROGRAM_STRING_ARB, 3 + POINTER_DWORDS);
   if (n) {
      GLubyte *programCopy = malloc(len);
      if (!programCopy) {
         _mesa_error(ctx, GL_OUT_OF_MEMORY, "glProgramStringARB");
         return;
      }
      memcpy(programCopy, string, len);
      n[1].e = target;
      n[2].e = format;
      n[3].i = len;
      save_pointer(&n[4], programCopy);
   }
   if (ctx->ExecuteFlag) {
      CALL_ProgramStringARB(ctx->Exec, (target, format, len, string));
   }
}
