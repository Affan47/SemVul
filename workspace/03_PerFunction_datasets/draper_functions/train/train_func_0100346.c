operator* (const Segment& seg, const Sphere& S)
  {
    if (seg.malformed() || S.malformed())
      return Segment(true);


    P dir(seg.end2() - seg.end1());
    dir *= 1.0/norm(dir);

    const P posn(S.center() - seg.end1());
    const P perp(posn%dir);

    if (S.radius() <= norm(perp))
      return Segment(true);


    const double B(dir|posn);
    const double C((posn|posn)-pow(S.radius(), 2));
    const double discrim(sqrt(B*B - C));

    return Segment(seg.end1() + (B-discrim)*dir,
		   seg.end1() + (B+discrim)*dir);
  }
