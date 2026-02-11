drawLevelFore()
{
  SDL_Rect pos;
  int x, y, n, i;


  for(y = global_params.start_y; y < global_params.end_y; y++) {
    for(x = global_params.start_x; x < global_params.end_x;) {
      i = x + (y * map.w);
      if(i < 0) {
        fprintf(stderr, "ERROR: x=%d y=%d start_x=%d start_y=%d i=%d\n", x, y,
                global_params.start_x, global_params.start_y, i);
        exit(1);
      }
      n = map.image_index[LEVEL_FORE][i];
      if(n != EMPTY_MAP) {


        pos.x =
          (global_params.offset_x + (x - global_params.start_x)) * TILE_W;
        pos.y =
          (global_params.offset_y + (y - global_params.start_y)) * TILE_H;
        pos.w = images[n]->image->w;
        pos.h = images[n]->image->h;


        pos.x += -cursor.pixel_x;
        pos.y += -cursor.pixel_y;

        SDL_BlitSurface(images[n]->image, NULL, screen, &pos);


        x += images[n]->image->w / TILE_W;
      } else {
        x++;
      }
    }
  }
}
