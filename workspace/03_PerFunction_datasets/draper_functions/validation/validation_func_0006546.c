IsDoubleBondGeometry()
  {
    double torsion;
    OBAtom *nbrStart,*nbrEnd;
    vector<OBBond*>::iterator i,j;


    if (_bgn->GetHyb()==1 || _bgn->GetValence()>3||
        _end->GetHyb()==1 || _end->GetValence()>3)
      return(true);

    for (nbrStart = static_cast<OBAtom*>(_bgn)->BeginNbrAtom(i); nbrStart;
         nbrStart = static_cast<OBAtom*>(_bgn)->NextNbrAtom(i))
      {
        if (nbrStart != _end)
          {
            for (nbrEnd = static_cast<OBAtom*>(_end)->BeginNbrAtom(j);
                 nbrEnd; nbrEnd = static_cast<OBAtom*>(_end)->NextNbrAtom(j))
              {
                if (nbrEnd != _bgn)
                  {
                    torsion=fabs(CalcTorsionAngle(nbrStart->GetVector(),
                                                  static_cast<OBAtom*>(_bgn)->GetVector(),
                                                  static_cast<OBAtom*>(_end)->GetVector(),
                                                  nbrEnd->GetVector()));


                    if (torsion > 15.0  && torsion < 160.0)
                      {

                        return(false);
                      }

                  }
              }
          }
      }
    return(true);
  }
