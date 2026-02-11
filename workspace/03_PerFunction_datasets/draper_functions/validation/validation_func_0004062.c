GetPointAlphaRange(double rng[2])
{
  if (vtkLookupTable* lut = vtkLookupTable::SafeDownCast(this->PointLookupTable))
    {
    lut->GetAlphaRange(rng);
    }
}
