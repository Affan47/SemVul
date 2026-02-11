rotateY(double delta) {
  double c1 = std::cos (delta);
  double s1 = std::sin (delta);
  HepLorentzVector rowx = row1();
  HepLorentzVector rowz = row3();
  HepLorentzVector r1 =  c1 * rowx + s1 * rowz;
  HepLorentzVector r3 = -s1 * rowx + c1 * rowz;
  mxx = r1.x();   mxy = r1.y();   mxz = r1.z();   mxt = r1.t();
  mzx = r3.x();   mzy = r3.y();   mzz = r3.z();   mzt = r3.t();
  return *this;
}
