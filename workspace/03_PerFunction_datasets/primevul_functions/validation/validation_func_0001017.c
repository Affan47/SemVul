bool HHVM_FUNCTION(imagegd, const Resource& image,
    const String& filename ) {
  return _php_image_output(image, filename, -1, -1, PHP_GDIMG_TYPE_GD, "GD",
                           (void (*)())gdImageGd);
}
