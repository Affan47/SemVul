HtmlString::HtmlString(GfxState *state, double fontSize, HtmlFontAccu* _fonts) : fonts(_fonts) {
  GfxFont *font;
  double x, y;

  state->transform(state->getCurX(), state->getCurY(), &x, &y);
  if ((font = state->getFont())) {
    double ascent = font->getAscent();
    double descent = font->getDescent();
    if( ascent > 1.05 ){

        ascent = 1.05;
    }
    if( descent < -0.4 ){

        descent = -0.4;
    }
    yMin = y - ascent * fontSize;
    yMax = y - descent * fontSize;
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    HtmlFont hfont=HtmlFont(font, static_cast<int>(fontSize-1), rgb);
    if (isMatRotOrSkew(state->getTextMat())) {
      double normalizedMatrix[4];
      memcpy(normalizedMatrix, state->getTextMat(), sizeof(normalizedMatrix));


      if (debug)
        std::cerr << DEBUG << "before transform: " << print_matrix(normalizedMatrix) << std::endl;
      normalizedMatrix[1] *= -1;
      normalizedMatrix[2] *= -1;
      if (debug)
        std::cerr << DEBUG << "after reflecting angle: " << print_matrix(normalizedMatrix) << std::endl;
      normalizeRotMat(normalizedMatrix);
      if (debug)
        std::cerr << DEBUG << "after norm: " << print_matrix(normalizedMatrix) << std::endl;
      hfont.setRotMat(normalizedMatrix);
    }
    fontpos = fonts->AddFont(hfont);
  } else {


    yMin = y - 0.95 * fontSize;
    yMax = y + 0.35 * fontSize;
    fontpos=0;
  }
  if (yMin == yMax) {


    yMin = y;
    yMax = y + 1;
  }
  col = 0;
  text = nullptr;
  xRight = nullptr;
  link = nullptr;
  len = size = 0;
  yxNext = nullptr;
  xyNext = nullptr;
  htext=new GooString();
  dir = textDirUnknown;
}
