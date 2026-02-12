Variant HHVM_FUNCTION(imagecolortransparent, const Resource& image,
                                             int64_t color ) {
  gdImagePtr im = get_valid_image_resource(image);
  if (!im) return false;
  if (color != -1) {

    gdImageColorTransparent(im, color);
  }
  return gdImageGetTransparent(im);
}
