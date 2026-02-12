bool HHVM_FUNCTION(imagegd2, const Resource& image,
    const String& filename ,
    int64_t chunk_size , int64_t type ) {
  return _php_image_output(image, filename, chunk_size, type,
                           PHP_GDIMG_TYPE_GD2, "GD2",
                           (void (*)())gdImageGd2);
}
