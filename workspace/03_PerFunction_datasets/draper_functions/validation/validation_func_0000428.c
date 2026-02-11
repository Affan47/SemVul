coeff1(){
  fraction mult = gauche->operator[](0)->nombre();
  mult.inverse();
  gauche->coeff(mult);
  droit->coeff(mult);
  simplifie();
  if (!redox() && valdefined()){
    val = val*mult.i/mult.d;
  }
}
