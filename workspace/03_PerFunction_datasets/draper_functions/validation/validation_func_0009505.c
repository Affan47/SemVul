SetFocalPoint(double x[3])
{
  if ( x[0] == this->FocalPoint[0] && x[1] == this->FocalPoint[1] &&
       x[2] == this->FocalPoint[2] )
    {
    return;
    }

  this->Modified();

  double v[3];
  for (int i=0; i<3; i++)
    {
    v[i] = x[i] - this->FocalPoint[i];
    this->FocalPoint[i] = x[i];

    if ( this->TranslationMode )
      {
      this->ModelBounds[2*i] += v[i];
      this->ModelBounds[2*i+1] += v[i];
      }
    else if ( this->Wrap )
      {
      this->FocalPoint[i] = this->ModelBounds[2*i] +
             fmod(static_cast<double>(
                    this->FocalPoint[i]-this->ModelBounds[2*i]),
                  static_cast<double>(
                    this->ModelBounds[2*i+1]-this->ModelBounds[2*i]));
      }
    else
      {
      if ( x[i] < this->ModelBounds[2*i] )
        {
        this->FocalPoint[i] = this->ModelBounds[2*i];
        }
      if ( x[i] > this->ModelBounds[2*i+1] )
        {
        this->FocalPoint[i] = this->ModelBounds[2*i+1];
        }
      }
    }
}
