_mesa_texstore_rgb565(TEXSTORE_PARAMS)
{
   ASSERT(dstFormat == MESA_FORMAT_B5G6R5_UNORM ||
          dstFormat == MESA_FORMAT_R5G6B5_UNORM);
   ASSERT(_mesa_get_format_bytes(dstFormat) == 2);

   if (!ctx->_ImageTransferState &&
       !srcPacking->SwapBytes &&
       baseInternalFormat == GL_RGB &&
       srcFormat == GL_RGB &&
       srcType == GL_UNSIGNED_BYTE &&
       dims == 2) {

      const GLint srcRowStride =
         _mesa_image_row_stride(srcPacking, srcWidth, srcFormat, srcType);
      const GLubyte *src = (const GLubyte *)
         _mesa_image_address(dims, srcPacking, srcAddr, srcWidth, srcHeight,
                             srcFormat, srcType, 0, 0, 0);
      GLubyte *dst = dstSlices[0];
      GLint row, col;
      for (row = 0; row < srcHeight; row++) {
         const GLubyte *srcUB = (const GLubyte *) src;
         GLushort *dstUS = (GLushort *) dst;

         if (dstFormat == MESA_FORMAT_B5G6R5_UNORM) {
            for (col = 0; col < srcWidth; col++) {
               dstUS[col] = PACK_COLOR_565( srcUB[0], srcUB[1], srcUB[2] );
               srcUB += 3;
            }
         }
         else {
            for (col = 0; col < srcWidth; col++) {
               dstUS[col] = PACK_COLOR_565_REV( srcUB[0], srcUB[1], srcUB[2] );
               srcUB += 3;
            }
         }
         dst += dstRowStride;
         src += srcRowStride;
      }
   }
   else {
      return store_ubyte_texture(ctx, dims, baseInternalFormat,
                                 dstFormat, dstRowStride, dstSlices,
                                 srcWidth, srcHeight, srcDepth,
                                 srcFormat, srcType, srcAddr, srcPacking);
   }
   return GL_TRUE;
}
