i830_destroy_context(struct intel_context *intel)
{
   GLuint i;
   struct i830_context *i830 = i830_context(&intel->ctx);

   intel_region_release(&i830->state.draw_region);
   intel_region_release(&i830->state.depth_region);

   for (i = 0; i < I830_TEX_UNITS; i++) {
      if (i830->state.tex_buffer[i] != NULL) {
	 drm_intel_bo_unreference(i830->state.tex_buffer[i]);
	 i830->state.tex_buffer[i] = NULL;
      }
   }

   _tnl_free_vertices(&intel->ctx);
}
