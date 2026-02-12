
    static CImg<T> get_load_rgb(const char *const filename, const unsigned int dimw, const unsigned int dimh=1) {
      return CImg<T>().load_rgb(filename,dimw,dimh);
}
