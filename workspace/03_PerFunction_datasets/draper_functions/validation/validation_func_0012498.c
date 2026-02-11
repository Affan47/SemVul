init(struct gl_context *ctx, const void *mem_ctx,
                     const char *input)
{


   this->location = -1;
   this->orig_name = input;
   this->is_clip_distance_mesa = false;
   this->skip_components = 0;
   this->next_buffer_separator = false;
   this->matched_candidate = NULL;

   if (ctx->Extensions.ARB_transform_feedback3) {

      if (strcmp(input, "gl_NextBuffer") == 0) {
         this->next_buffer_separator = true;
         return;
      }


      if (strcmp(input, "gl_SkipComponents1") == 0)
         this->skip_components = 1;
      else if (strcmp(input, "gl_SkipComponents2") == 0)
         this->skip_components = 2;
      else if (strcmp(input, "gl_SkipComponents3") == 0)
         this->skip_components = 3;
      else if (strcmp(input, "gl_SkipComponents4") == 0)
         this->skip_components = 4;

      if (this->skip_components)
         return;
   }


   const char *base_name_end;
   long subscript = parse_program_resource_name(input, &base_name_end);
   this->var_name = ralloc_strndup(mem_ctx, input, base_name_end - input);
   if (subscript >= 0) {
      this->array_subscript = subscript;
      this->is_subscripted = true;
   } else {
      this->is_subscripted = false;
   }


   if (ctx->ShaderCompilerOptions[MESA_SHADER_VERTEX].LowerClipDistance &&
       strcmp(this->var_name, "gl_ClipDistance") == 0) {
      this->is_clip_distance_mesa = true;
   }
}
