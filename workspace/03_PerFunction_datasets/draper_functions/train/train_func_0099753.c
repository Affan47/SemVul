getAmPlatzen() const {
  if (mPos.r == richtung_keins)
    return false;


  CASSERT(mPos.r == richtung_einzel ||
         mBlop[0].getAmPlatzen() == mBlop[1].getAmPlatzen());

  return mBlop[0].getAmPlatzen();
}
