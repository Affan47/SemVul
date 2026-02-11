axisSetGraphLimits(CoordSettings coord, const Transform* transform,
  double* xThetaMin, double* xThetaMax, double* yRMin, double* yRMax)
{

  QList<QRect> updateRectList;
  updateGraphCoordinates(coord, transform, &updateRectList);


  return axesPointSet.pointSetGraphLimits(xThetaMin, xThetaMax, yRMin, yRMax);
}
