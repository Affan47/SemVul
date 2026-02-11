symmetry_copy_near(const Spacegroup& spgr, const Cell& cell, const Coord_frac& n) const {
  Coord_frac c, cmin(*this);
  double d2, d2min(1.0e12);
  for ( int k = 0; k < spgr.num_symops(); k++ ) {
    c = spgr.symop(k) * (*this);
    c = c.lattice_copy_near( n );
    d2 = ( c - n ).lengthsq( cell );
    if ( d2 < d2min ) {
      d2min = d2;
      cmin = c;
    }
  }
  return cmin;
}
