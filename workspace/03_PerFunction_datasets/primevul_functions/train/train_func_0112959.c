
    CImg<T>& RGBtoLab(const bool use_D65=true) {
      return RGBtoXYZ(use_D65).XYZtoLab(use_D65);
}
