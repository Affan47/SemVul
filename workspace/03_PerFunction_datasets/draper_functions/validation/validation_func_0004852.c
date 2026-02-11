SetPointsBoundingBoxCoordinates(const float * coordinates)
{
  assert(coordinates);

  if (PointsBoundingBoxCoordinates == 0) PointsBoundingBoxCoordinates = new float[6];

  PointsBoundingBoxCoordinates[0] = coordinates[0];
  PointsBoundingBoxCoordinates[1] = coordinates[1];
  PointsBoundingBoxCoordinates[2] = coordinates[2];
  PointsBoundingBoxCoordinates[3] = coordinates[3];
  PointsBoundingBoxCoordinates[4] = coordinates[4];
  PointsBoundingBoxCoordinates[5] = coordinates[5];
}
