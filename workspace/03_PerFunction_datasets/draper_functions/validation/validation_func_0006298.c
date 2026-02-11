FindSmallestRing() const
  {
    vector<OBRing*> rlist;
    vector<OBRing*>::iterator i;

    OBMol *mol = (OBMol*)((OBBond*)this)->GetParent();

    rlist = mol->GetSSSR();
    OBRing* result = (OBRing*) NULL;
    size_t min_size = UINT_MAX;
    for (i = rlist.begin();i != rlist.end();++i) {
      if ((*i)->IsMember((OBBond*)this) && (*i)->Size() < min_size) {
        min_size = (*i)->Size();
        result = *i;
      }
    }
    return result;
  }
