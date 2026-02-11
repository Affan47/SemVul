compile_clip_prog( struct brw_context *brw,
			     struct brw_clip_prog_key *key )
{
   struct brw_clip_compile c;
   const GLuint *program;
   void *mem_ctx;
   GLuint program_size;
   GLuint i;

   memset(&c, 0, sizeof(c));

   mem_ctx = ralloc_context(NULL);


   brw_init_compile(brw, &c.func, mem_ctx);

   c.func.single_program_flow = 1;

   c.key = *key;
   c.vue_map = brw->vue_map_geom_out;

   c.has_flat_shading =
      brw_any_flat_varyings(&key->interpolation_mode);
   c.has_noperspective_shading =
      brw_any_noperspective_varyings(&key->interpolation_mode);


   c.nr_regs = (c.vue_map.num_slots + 1)/2;

   c.prog_data.clip_mode = c.key.clip_mode;


   brw_set_mask_control(&c.func, BRW_MASK_DISABLE);


   switch (key->primitive) {
   case GL_TRIANGLES:
      if (key->do_unfilled)
	 brw_emit_unfilled_clip( &c );
      else
	 brw_emit_tri_clip( &c );
      break;
   case GL_LINES:
      brw_emit_line_clip( &c );
      break;
   case GL_POINTS:
      brw_emit_point_clip( &c );
      break;
   default:
      assert(0);
      return;
   }


   program = brw_get_program(&c.func, &program_size);

   if (unlikely(INTEL_DEBUG & DEBUG_CLIP)) {
      printf("clip:\n");
      for (i = 0; i < program_size / sizeof(struct brw_instruction); i++)
	 brw_disasm(stdout, &((struct brw_instruction *)program)[i],
		    brw->gen);
      printf("\n");
   }

   brw_upload_cache(&brw->cache,
		    BRW_CLIP_PROG,
		    &c.key, sizeof(c.key),
		    program, program_size,
		    &c.prog_data, sizeof(c.prog_data),
		    &brw->clip.prog_offset, &brw->clip.prog_data);
   ralloc_free(mem_ctx);
}
