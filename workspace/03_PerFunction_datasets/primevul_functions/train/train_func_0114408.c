
    CImg<Tfloat> get_shift_object3d() const {
      return CImg<Tfloat>(*this,false).shift_object3d();
}
