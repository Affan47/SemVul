rects_overlap_h(Rect *a, Rect *b) {
  return (b->y1 <= a->y1 && a->y1 <= b->y2) ||
         (a->y1 <= b->y1 && b->y1 <= a->y2);
}
