intel_bufferobj_subdata(struct gl_context * ctx,
                        GLintptrARB offset,
                        GLsizeiptrARB size,
                        const GLvoid * data, struct gl_buffer_object *obj)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_buffer_object *intel_obj = intel_buffer_object(obj);
   bool busy;

   if (size == 0)
      return;

   assert(intel_obj);


   if (intel_obj->sys_buffer) {
      if (intel_obj->source)
	 release_buffer(intel_obj);

      if (intel_obj->buffer == NULL) {
	 memcpy((char *)intel_obj->sys_buffer + offset, data, size);
	 return;
      }

      _mesa_align_free(intel_obj->sys_buffer);
      intel_obj->sys_buffer = NULL;
   }


   busy =
      drm_intel_bo_busy(intel_obj->buffer) ||
      drm_intel_bo_references(intel->batch.bo, intel_obj->buffer);

   if (busy) {
      if (size == intel_obj->Base.Size) {

	 drm_intel_bo_unreference(intel_obj->buffer);
	 intel_bufferobj_alloc_buffer(intel, intel_obj);
	 drm_intel_bo_subdata(intel_obj->buffer, 0, size, data);
      } else {
         perf_debug("Using a blit copy to avoid stalling on %ldb "
                    "glBufferSubData() to a busy buffer object.\n",
                    (long)size);
	 drm_intel_bo *temp_bo =
	    drm_intel_bo_alloc(intel->bufmgr, "subdata temp", size, 64);

	 drm_intel_bo_subdata(temp_bo, 0, size, data);

	 intel_emit_linear_blit(intel,
				intel_obj->buffer, offset,
				temp_bo, 0,
				size);

	 drm_intel_bo_unreference(temp_bo);
      }
   } else {
      drm_intel_bo_subdata(intel_obj->buffer, offset, size, data);
   }
}
