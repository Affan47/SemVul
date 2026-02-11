ComputeBoundaryNormal(vtkPoints* points, double* barycenter, double* normal)
{
  int numberOfPoints;
  double point[3], vector1[3], vector0[3], cross[3], sumCross[3] = {0.0f,0.0f,0.0f};
  vtkIdType i, j;


  numberOfPoints = points->GetNumberOfPoints();

  points->GetPoint(numberOfPoints-1,point);
  vector0[0] = point[0] - barycenter[0];
  vector0[1] = point[1] - barycenter[1];
  vector0[2] = point[2] - barycenter[2];

  for (i=0; i<numberOfPoints; i++)
    {
    points->GetPoint(i,point);
    vector1[0] = point[0] - barycenter[0];
    vector1[1] = point[1] - barycenter[1];
    vector1[2] = point[2] - barycenter[2];

    vtkMath::Cross(vector1,vector0,cross);

    for (j=0; j<3; j++)
      {
      vector0[j] = vector1[j];
      sumCross[j] += cross[j];
      }
    }

  vtkMath::Normalize(sumCross);

  for (j=0; j<3; j++)
    {
    normal[j] = sumCross[j];
    }
}
