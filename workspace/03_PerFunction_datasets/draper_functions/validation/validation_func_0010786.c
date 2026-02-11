getPixels(std::strstream& in) {

  while((in.pcount() - in.tellg()) >= 3 && in.good() && !in.eof()) {
    u_char r, g, b;
    in.get((char&)r);
    in.get((char&)g);
    in.get((char&)b);

    poke(float(r)/0xff, float(g)/0xff, float(b)/0xff);
  }
}
