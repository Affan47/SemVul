bool HHVM_FUNCTION(imagejpeg, const Resource& image,
    const String& filename , int64_t quality ) {
  return _php_image_output_ctx(image, filename, quality, -1,
                               PHP_GDIMG_TYPE_JPG, "JPEG",
                               (void (*)())gdImageJpegCtx);
}
