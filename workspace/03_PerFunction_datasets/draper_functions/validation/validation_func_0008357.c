ComputeEdgeError(double x[3], double x1[3], double x2[3])
{
  double projDist = vtkLine::DistanceToLine(x, x1, x2);
  double edgeLength = vtkMath::Distance2BetweenPoints(x1,x2);

  return (projDist < edgeLength ? projDist : edgeLength);
}
