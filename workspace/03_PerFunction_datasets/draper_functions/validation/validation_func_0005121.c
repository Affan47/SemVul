merkeAlteVarWerte() {
  CASSERT(gGleichZeit);
  if (mZeitNummerDatenAlt < gAktuelleZeitNummerDatenAlt) {
    for (int i = 0; i < mDatenLaenge; i++)
      mDatenAlt[i] = mDaten[i];
    mZeitNummerDatenAlt = gAktuelleZeitNummerDatenAlt;
  }
}
