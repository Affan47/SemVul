void HtmlPage::addChar(GfxState *state, double x, double y,
		       double dx, double dy,
			double ox, double oy, Unicode *u, int uLen) {
  double x1, y1, w1, h1, dx2, dy2;
  int n, i;
  state->transform(x, y, &x1, &y1);
  n = curStr->len;


  if (debug) {
    const double *text_mat = state->getTextMat();


    if (text_mat[0] < 0 || !is_within(text_mat[1], .1, 0)) {
      std::cerr << DEBUG << "rotation matrix for \"" << print_uni_str(u, uLen) << '"' << std::endl;
      std::cerr << "text " << print_matrix(state->getTextMat());
    }
  }
  if (n > 0 &&


      fabs(x1 - curStr->xRight[n-1]) > wordBreakThreshold * (curStr->yMax - curStr->yMin) &&


      !rot_matrices_equal(curStr->getFont().getRotMat(), state->getTextMat()))
  {
    endString();
    beginString(state, nullptr);
  }
  state->textTransformDelta(state->getCharSpace() * state->getHorizScaling(),
			    0, &dx2, &dy2);
  dx -= dx2;
  dy -= dy2;
  state->transformDelta(dx, dy, &w1, &h1);
  if (uLen != 0) {
    w1 /= uLen;
    h1 /= uLen;
  }
  for (i = 0; i < uLen; ++i) {
    curStr->addChar(state, x1 + i*w1, y1 + i*h1, w1, h1, u[i]);
  }
}
