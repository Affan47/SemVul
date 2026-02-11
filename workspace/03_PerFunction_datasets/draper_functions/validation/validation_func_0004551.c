flag_grid_init(struct flag_grid *fg, int w, int h) {
  fg->width = MIN(w, MAX_WIDTH);
  fg->height = MIN(h, MAX_HEIGHT);
  int i, j;
  for(i=0; i<fg->width; ++i) {
    for(j=0; j<fg->height; ++j) {
      fg->flag[i][j] = FLAG_OFF;
      fg->call[i][j] = 0;
    }
  }
}
