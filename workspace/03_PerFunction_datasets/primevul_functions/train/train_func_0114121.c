
    CImg<Tfloat> get_RGBtoYUV() const {
      return CImg<Tfloat>(*this,false).RGBtoYUV();
}
