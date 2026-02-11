HasNonZeroCoords()
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator i;

    for (atom = BeginAtom(i);atom;atom = NextAtom(i))
      if (atom->GetVector() != VZero)
        return(true);

    return(false);
  }
