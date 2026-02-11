calcWidth(bool) {


  if (ps == 0.) return;


  if (id1Abs < 17 && id2Abs < 17) {
    widNow    = preFac * pow2(yukawa[(id1Abs-9)/2][(id2Abs-9)/2]) * ps;
    if (id2Abs != id1Abs) widNow *= 2.;
  }


  else if (id1Abs == idWR && id2Abs == idWR)
    widNow    = preFac * pow2(yukawa[(id1Abs-9)/2][(id2Abs-9)/2]) * ps;

}
