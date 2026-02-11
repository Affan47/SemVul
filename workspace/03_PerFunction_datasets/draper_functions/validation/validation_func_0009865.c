is_nodata(short x) {
  return (x == nodataType::ELEVATION_BOUNDARY ||
		  x == nodataType::ELEVATION_NODATA);
}
