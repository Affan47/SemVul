bool HHVM_FUNCTION(imagecolordeallocate, const Resource& image,
                                         int64_t color) {
  gdImagePtr im = get_valid_image_resource(image);
  if (!im) return false;


  if (gdImageTrueColor(im)) return true;

  if (color >= 0 && color < gdImageColorsTotal(im)) {
    gdImageColorDeallocate(im, color);
    return true;
  } else {
    raise_warning("Color index %" PRId64 " out of range", color);
    return false;
  }
}
