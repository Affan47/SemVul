_php_image_output(const Resource& image, const String& filename, int quality,
                  int type, int image_type, char* , void (*func_p)()) {
  gdImagePtr im = get_valid_image_resource(image);
  if (!im) return false;
  req::ptr<File> file;
  FILE *fp;
  int q = quality, i, t = type;


  if (!filename.empty()) {
    file = php_open_plain_file(filename, "wb", &fp);
    if (!file) {
      raise_warning("Unable to open '%s' for writing", filename.c_str());
      return false;
    }

    switch (image_type) {
    case PHP_GDIMG_CONVERT_WBM:
      if (q == -1) {
        q = 0;
      } else if (q < 0 || q > 255) {
        raise_warning("Invalid threshold value '%d'. "
                        "It must be between 0 and 255", q);
        q = 0;
      }
      gdImageWBMP(im, q, fp);
      break;
    case PHP_GDIMG_TYPE_JPG: {

      ((void(*)(gdImagePtr, FILE *, int))(func_p))(im, fp, q);
      break;
    }
    case PHP_GDIMG_TYPE_WBM:
      for (i = 0; i < gdImageColorsTotal(im); i++) {
        if (gdImageRed(im, i) == 0) break;
      }

      ((void(*)(gdImagePtr, int, FILE *))(func_p))(im, i, fp);
      break;
    case PHP_GDIMG_TYPE_GD:
      if (im->trueColor) {
        gdImageTrueColorToPalette(im,1,256);
      }

      ((void(*)(gdImagePtr, FILE *))(func_p))(im, fp);
      break;
    case PHP_GDIMG_TYPE_GD2:
      if (q == -1) {
        q = 128;
      }

      ((void(*)(gdImagePtr, FILE *, int, int))(func_p))(im, fp, q, t);
      break;
    default:
      if (q == -1) {
        q = 128;
      }
      ((void(*)(gdImagePtr, FILE *, int, int))(func_p))(im, fp, q, t);
      break;
    }
    fflush(fp);
    file->close();
  } else {
    int   b;
    FILE *tmp;
    char  buf[4096];
    char path[PATH_MAX];


    snprintf(path, sizeof(path), "/tmp/XXXXXX");
    int fd = mkstemp(path);
    if (fd == -1 || (tmp = fdopen(fd, "r+b")) == nullptr) {
      if (fd != -1) close(fd);
      raise_warning("Unable to open temporary file");
      return false;
    }

    switch (image_type) {
    case PHP_GDIMG_CONVERT_WBM:
       if (q == -1) {
          q = 0;
        } else if (q < 0 || q > 255) {
          raise_warning("Invalid threshold value '%d'. "
                          "It must be between 0 and 255", q);
         q = 0;
        }
      gdImageWBMP(im, q, tmp);
      break;
    case PHP_GDIMG_TYPE_JPG:
      ((void(*)(gdImagePtr, FILE *, int))(func_p))(im, tmp, q);
      break;
    case PHP_GDIMG_TYPE_WBM:
      for (i = 0; i < gdImageColorsTotal(im); i++) {
        if (gdImageRed(im, i) == 0) {
          break;
        }
      }
      ((void(*)(gdImagePtr, int, FILE *))(func_p))(im, q, tmp);
      break;
    case PHP_GDIMG_TYPE_GD:
      if (im->trueColor) {
        gdImageTrueColorToPalette(im,1,256);
      }
      ((void(*)(gdImagePtr, FILE *))(func_p))(im, tmp);
      break;
    case PHP_GDIMG_TYPE_GD2:
      if (q == -1) {
        q = 128;
      }
      ((void(*)(gdImagePtr, FILE *, int, int))(func_p))(im, tmp, q, t);
      break;
    default:
      ((void(*)(gdImagePtr, FILE *))(func_p))(im, tmp);
      break;
    }

    fseek(tmp, 0, SEEK_SET);

    while ((b = fread(buf, 1, sizeof(buf), tmp)) > 0) {
      g_context->write(buf, b);
    }

    fclose(tmp);

    unlink((const char *)path);
  }
  return true;
}
