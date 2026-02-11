point(
	double yy,
	double lo,
	double hi,
	int scale,
	int offset,
	int linswp)
{
  int place;

  if (linswp) {
    place = round_to_int( scale*(yy-lo)/(hi-lo));
  }else{untested();
    place = round_to_int( scale*(log(yy/lo))/(log(hi/lo)));
  }

  if (place < 0) {
    place = 0;
  }
  if (place > scale) {itested();
    place = scale;
  }
  return  place + offset;
}
