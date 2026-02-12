bool HHVM_FUNCTION(image2wbmp, const Resource& image,
                   const String& filename ,
                   int64_t threshold ) {
  return _php_image_output(image, filename, threshold, -1,
                           PHP_GDIMG_CONVERT_WBM, "WBMP",
                           (void (*)())_php_image_bw_convert);
}
