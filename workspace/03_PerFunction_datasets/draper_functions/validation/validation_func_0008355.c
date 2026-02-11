rotationOf (const Hep3Vector & vec,
                       const Hep3Vector & axis, double ddelta) {
  Hep3Vector vv(vec);
  return vv.rotate(axis, ddelta);
}
