intelAllocateBuffer(__DRIscreen *screen,
		    unsigned attachment, unsigned format,
		    int width, int height)
{
   struct intel_buffer *intelBuffer;
   struct intel_screen *intelScreen = screen->driverPrivate;

   assert(attachment == __DRI_BUFFER_FRONT_LEFT ||
          attachment == __DRI_BUFFER_BACK_LEFT);

   intelBuffer = calloc(1, sizeof *intelBuffer);
   if (intelBuffer == NULL)
      return NULL;


   intelBuffer->region = intel_region_alloc(intelScreen,
                                            I915_TILING_X,
                                            format / 8,
                                            width,
                                            height,
                                            true);

   if (intelBuffer->region == NULL) {
	   free(intelBuffer);
	   return NULL;
   }

   intel_region_flink(intelBuffer->region, &intelBuffer->base.name);

   intelBuffer->base.attachment = attachment;
   intelBuffer->base.cpp = intelBuffer->region->cpp;
   intelBuffer->base.pitch = intelBuffer->region->pitch;

   return &intelBuffer->base;
}
