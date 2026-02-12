
    CImg<Tfloat> get_xyYtoXYZ() const {
      return CImg<Tfloat>(*this,false).xyYtoXYZ();
}
