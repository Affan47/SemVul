
    CImg<Tfloat> get_resize_object3d() const {
      return CImg<Tfloat>(*this,false).resize_object3d();
}
