calcObjectSpaceData(SoState * ownerstate)
{
  this->calcMatrices(ownerstate);

  SbVec3d start, dir;

  if (this->objectspacevalid) {
    this->world2obj.multVecMatrix(this->raystart, start);
    this->world2obj.multDirMatrix(this->raydirection, dir);
    this->osline = SbDPLine(start, start + dir);

    SbVec3f tmp1, tmp2;
    tmp1.setValue(start);


    dir *= this->rayfar;
    tmp2.setValue(dir);

    this->osline_sp = SbLine(tmp1, tmp1 + tmp2);
  }
}
