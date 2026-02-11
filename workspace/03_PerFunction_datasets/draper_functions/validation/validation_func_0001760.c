AdjustAndCheckRectangle(const WebPPicture* const pic,
                                   int* const left, int* const top,
                                   int width, int height) {
  SnapTopLeftPosition(pic, left, top);
  if ((*left) < 0 || (*top) < 0) return 0;
  if (width <= 0 || height <= 0) return 0;
  if ((*left) + width > pic->width) return 0;
  if ((*top) + height > pic->height) return 0;
  return 1;
}
