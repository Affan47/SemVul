bool HHVM_FUNCTION(imagepng, const Resource& image,
    const String& filename ,
    int64_t quality , int64_t filters ) {
  return _php_image_output_ctx(image, filename, quality, filters,
                               PHP_GDIMG_TYPE_PNG, "PNG",
                               (void (*)())gdImagePngCtxEx);
}
