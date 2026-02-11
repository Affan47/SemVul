rollover_box(Gameboard *g, buttonstate *b){
  GdkRectangle r;
  int width = g->g.width;
  int height = g->g.height;

  int x = b->x - b->ex.width/2 + b->ex.x_bearing -2;
  int y = b->y - BUTTON_RADIUS - BUTTON_TEXT_BORDER + b->ex.y_bearing -2;

  if(x<BUTTON_TEXT_BORDER)x=BUTTON_TEXT_BORDER;
  if(y<BUTTON_TEXT_BORDER)y=BUTTON_TEXT_BORDER;
  if(x+b->ex.width >= width - BUTTON_TEXT_BORDER)
    x = width - BUTTON_TEXT_BORDER - b->ex.width;
  if(y+b->ex.height >= height - BUTTON_TEXT_BORDER)
    y = height - BUTTON_TEXT_BORDER - b->ex.height;

  r.x=x;
  r.y=y;
  r.width=b->ex.width+5;
  r.height=b->ex.height+5;

  return r;
}
