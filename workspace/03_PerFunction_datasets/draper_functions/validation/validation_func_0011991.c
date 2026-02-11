EvaluateLocation (int &vtkNotUsed (subId),
  double pcoords[3], double x[3], double *weights)
{
  int i, j;
  double pt[3];

  this->InterpolationFunctions (pcoords, weights);

  x[0] = x[1] = x[2] = 0.0;
  for (i = 0; i < 27; i++)
    {
    this->Points->GetPoint (i, pt);
    for (j = 0; j < 3; j++)
      {
      x[j] += pt[j] * weights[i];
      }
    }
}
