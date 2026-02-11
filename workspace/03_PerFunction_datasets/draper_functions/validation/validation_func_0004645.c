makeTransformation(const KEYGeometry &geometry)
{
  using namespace transformations;

  KEYTransformation tr;

  const double w = geometry.naturalSize.width;
  const double h = geometry.naturalSize.height;

  tr *= origin(w, h);


  if (geometry.shearXAngle || geometry.shearYAngle)
    tr *= shear(get_optional_value_or(geometry.shearXAngle, 0), get_optional_value_or(geometry.shearYAngle, 0));

  if (geometry.horizontalFlip)
    tr *= flip(get(geometry.horizontalFlip), false);
  if (geometry.verticalFlip)
    tr *= flip(false, get(geometry.verticalFlip));

  if (geometry.angle)
    tr *= rotate(get(geometry.angle));

  tr *= center(w, h);
  tr *= translate(geometry.position.x, geometry.position.y);

  return tr;
}
