Variant HHVM_FUNCTION(imagecropauto,
                      const Resource& image,
                      int64_t mode ,
                      double threshold ,
                      int64_t color ) {
  gdImagePtr im = get_valid_image_resource(image);
  if (!im) return false;
  gdImagePtr imcropped = nullptr;
  switch (mode) {
    case -1:
      mode = GD_CROP_DEFAULT;
    case GD_CROP_DEFAULT:
    case GD_CROP_TRANSPARENT:
    case GD_CROP_BLACK:
    case GD_CROP_WHITE:
    case GD_CROP_SIDES:
      imcropped = gdImageCropAuto(im, mode);
      break;

    case GD_CROP_THRESHOLD:
      if (color < 0) {
        raise_warning("imagecropauto(): Color argument missing "
                      "with threshold mode");
        return false;
      }
      imcropped = gdImageCropThreshold(im, color, (float) threshold);
      break;

    default:
      raise_warning("imagecropauto(): Unknown crop mode");
      return false;
  }
  if (!imcropped) {
    return false;
  }
  return Variant(req::make<Image>(imcropped));
}
