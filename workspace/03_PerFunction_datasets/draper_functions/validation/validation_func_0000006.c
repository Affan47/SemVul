animate_mouse_cursor(void)
{
  static int cursor_frame = 0;

  if (!mouse_cursor_changed) {
    return;
  }

  if (mouse_cursor_type != CURSOR_DEFAULT) {
    if (!gui_sdl_do_cursor_animation
        || (cursor_frame == NUM_CURSOR_FRAMES)) {
      cursor_frame = 0;
    }

    if (gui_sdl_use_color_cursors) {
      current_color_cursor.cursor = GET_SURF(get_cursor_sprite(tileset,
                                    mouse_cursor_type,
                                    &current_color_cursor.hot_x,
                                    &current_color_cursor.hot_y, cursor_frame));
    } else {
      SDL_SetCursor(fc_cursors[mouse_cursor_type][cursor_frame]);
    }

    cursor_frame++;
  }
}
