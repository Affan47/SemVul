background(const BColor &c) {
  unsigned int i, wh = width * height;

  bg = c;

  for (i = 0; i < wh; i++) {
    *(red + i) = c.red;
    *(green + i) = c.green;
    *(blue + i) = c.blue;
  }
}
