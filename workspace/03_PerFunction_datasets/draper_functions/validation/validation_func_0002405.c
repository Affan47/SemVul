Scale(double x, double y)
{
  if (x == 1.0 && y == 1.0)
    {
    return;
    }
  double matrix[3][3];
  vtkMatrix3x3::Identity(*matrix);
  matrix[0][0] = x;
  matrix[1][1] = y;
  this->Matrix->Multiply3x3(this->Matrix->GetData(), *matrix,
                            this->Matrix->GetData());
  this->Matrix->Modified();
}
