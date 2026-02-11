FunctionGradient(const double x[3], double g[3])
{
  if ( ! this->Transform )
    {
    this->EvaluateGradient(const_cast<double *>(x),g);
    }
  else
    {
    double pt[3];
    double A[3][3];
    this->Transform->Update();
    this->Transform->InternalTransformDerivative(x,pt,A);
    this->EvaluateGradient(static_cast<double *>(pt),g);


    vtkMath::Transpose3x3(A,A);
    vtkMath::Multiply3x3(A,g,g);


    if (vtkMath::Determinant3x3(A) < 0)
      {
      g[0] = -g[0];
      g[1] = -g[1];
      g[2] = -g[2];
      }
    }
}
