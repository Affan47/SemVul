do_blit_readpixels(struct gl_context * ctx,
                   GLint x, GLint y, GLsizei width, GLsizei height,
                   GLenum format, GLenum type,
                   const struct gl_pixelstore_attrib *pack, GLvoid * pixels)
{
   struct brw_context *brw = brw_context(ctx);
   struct intel_buffer_object *dst = intel_buffer_object(pack->BufferObj);
   GLuint dst_offset;
   drm_intel_bo *dst_buffer;
   GLint dst_x, dst_y;
   GLuint dirty;

   DBG("%s\n", __FUNCTION__);

   assert(_mesa_is_bufferobj(pack->BufferObj));

   struct gl_renderbuffer *rb = ctx->ReadBuffer->_ColorReadBuffer;
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);


   if (!_mesa_is_color_format(format))
      return false;

   assert(irb != NULL);

   if (ctx->_ImageTransferState ||
       !_mesa_format_matches_format_and_type(irb->mt->format, format, type,
                                             false)) {
      DBG("%s - bad format for blit\n", __FUNCTION__);
      return false;
   }

   if (pack->SwapBytes || pack->LsbFirst) {
      DBG("%s: bad packing params\n", __FUNCTION__);
      return false;
   }

   int dst_stride = _mesa_image_row_stride(pack, width, format, type);
   bool dst_flip = false;


   struct gl_pixelstore_attrib uninverted_pack = *pack;
   if (pack->Invert) {
      dst_stride = -dst_stride;
      dst_flip = true;
      uninverted_pack.Invert = false;
   }

   dst_offset = (GLintptr)pixels;
   dst_offset += _mesa_image_offset(2, &uninverted_pack, width, height,
				    format, type, 0, 0, 0);

   if (!_mesa_clip_copytexsubimage(ctx,
				   &dst_x, &dst_y,
				   &x, &y,
				   &width, &height)) {
      return true;
   }

   dirty = brw->front_buffer_dirty;
   intel_prepare_render(brw);
   brw->front_buffer_dirty = dirty;

   dst_buffer = intel_bufferobj_buffer(brw, dst,
				       dst_offset, height * dst_stride);

   struct intel_mipmap_tree *pbo_mt =
      intel_miptree_create_for_bo(brw,
                                  dst_buffer,
                                  irb->mt->format,
                                  dst_offset,
                                  width, height,
                                  dst_stride, I915_TILING_NONE);

   if (!intel_miptree_blit(brw,
                           irb->mt, irb->mt_level, irb->mt_layer,
                           x, y, _mesa_is_winsys_fbo(ctx->ReadBuffer),
                           pbo_mt, 0, 0,
                           0, 0, dst_flip,
                           width, height, GL_COPY)) {
      return false;
   }

   intel_miptree_release(&pbo_mt);

   DBG("%s - DONE\n", __FUNCTION__);

   return true;
}
