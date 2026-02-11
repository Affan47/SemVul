base_set_mapview_origin(int gui_x0, int gui_y0)
{
  int old_gui_x0, old_gui_y0, dx, dy;
  const int width = mapview.width, height = mapview.height;
  int common_x0, common_x1, common_y0, common_y1;
  int update_x0, update_x1, update_y0, update_y1;


  normalize_gui_pos(tileset, &gui_x0, &gui_y0);
  gui_distance_vector(tileset, &dx, &dy,
		      mapview.gui_x0, mapview.gui_y0,
		      gui_x0, gui_y0);
  old_gui_x0 = gui_x0 - dx;
  old_gui_y0 = gui_y0 - dy;

  mapview.gui_x0 = gui_x0;
  mapview.gui_y0 = gui_y0;


  common_x0 = MAX(old_gui_x0, gui_x0);
  common_x1 = MIN(old_gui_x0, gui_x0) + width;
  common_y0 = MAX(old_gui_y0, gui_y0);
  common_y1 = MIN(old_gui_y0, gui_y0) + height;

  if (mapview.can_do_cached_drawing
      && common_x1 > common_x0 && common_y1 > common_y0) {


    struct canvas *target = mapview.tmp_store;

    if (old_gui_x0 < gui_x0) {
      update_x0 = MAX(old_gui_x0 + width, gui_x0);
      update_x1 = gui_x0 + width;
    } else {
      update_x0 = gui_x0;
      update_x1 = MIN(old_gui_x0, gui_x0 + width);
    }
    if (old_gui_y0 < gui_y0) {
      update_y0 = MAX(old_gui_y0 + height, gui_y0);
      update_y1 = gui_y0 + height;
    } else {
      update_y0 = gui_y0;
      update_y1 = MIN(old_gui_y0, gui_y0 + height);
    }

    dirty_all();
    canvas_copy(target, mapview.store,
		common_x0 - old_gui_x0,
		common_y0 - old_gui_y0,
		common_x0 - gui_x0, common_y0 - gui_y0,
		common_x1 - common_x0, common_y1 - common_y0);
    mapview.tmp_store = mapview.store;
    mapview.store = target;

    if (update_y1 > update_y0) {
      update_map_canvas(0, update_y0 - gui_y0,
			width, update_y1 - update_y0);
    }
    if (update_x1 > update_x0) {
      update_map_canvas(update_x0 - gui_x0, common_y0 - gui_y0,
			update_x1 - update_x0, common_y1 - common_y0);
    }
  } else {
    dirty_all();
    update_map_canvas(0, 0, mapview.store_width, mapview.store_height);
  }

  center_tile_overviewcanvas();
  if (hover_state == HOVER_GOTO || hover_state == HOVER_PATROL) {
    create_line_at_mouse_pos();
  }
  if (rectangle_active) {
    update_rect_at_mouse_pos();
  }
}
