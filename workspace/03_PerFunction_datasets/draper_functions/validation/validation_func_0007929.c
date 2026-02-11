operator&=(const vtkAMRBox &other)
{
  if (this->Dimension!=other.Dimension)
    {
    vtkGenericWarningMacro(
      "Can't operate on a " << this->Dimension
      << "D box with a " << other.Dimension << "D box.");
    return;
    }
  if (this->Empty())
    {
    return;
    }
  if (other.Empty())
    {
    this->Invalidate();
    return;
    }

  int otherLo[3];
  int otherHi[3];
  other.GetDimensions(otherLo,otherHi);
  int lo[3];
  int hi[3];
  for (int q=0; q<this->Dimension; ++q)
    {
    lo[q]=(this->LoCorner[q]>otherLo[q] ? this->LoCorner[q] : otherLo[q]);
    hi[q]=(this->HiCorner[q]<otherHi[q] ? this->HiCorner[q] : otherHi[q]);
    }
  this->SetDimensions(lo,hi);
}
