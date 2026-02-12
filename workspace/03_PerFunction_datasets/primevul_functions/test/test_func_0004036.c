bool PBMotion::operator==(const PBMotion& b) const
{
  const PBMotion& a = *this;


  for (int i=0;i<2;i++) {
    if (a.predFlag[i] != b.predFlag[i]) return false;

    if (a.predFlag[i]) {
      if (a.mv[i].x != b.mv[i].x) return false;
      if (a.mv[i].y != b.mv[i].y) return false;
      if (a.refIdx[i] != b.refIdx[i]) return false;
    }
  }

  return true;
}
