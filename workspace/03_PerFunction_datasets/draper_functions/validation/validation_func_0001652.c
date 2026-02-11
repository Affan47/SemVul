ShallowCopy( vtkColorTransferFunction *f )
{
  if (f != NULL)
    {
    this->Superclass::DeepCopy(f);

    this->Clamping     = f->Clamping;
    this->ColorSpace   = f->ColorSpace;
    this->HSVWrap      = f->HSVWrap;
    this->Scale        = f->Scale;

    int i;
    this->RemoveAllPoints();
    for ( i = 0; i < f->GetSize(); i++ )
      {
      double val[6];
      f->GetNodeValue(i, val);
      this->AddRGBPoint(val[0], val[1], val[2], val[3], val[4], val[5]);
      }
    this->Modified();
    }
}
