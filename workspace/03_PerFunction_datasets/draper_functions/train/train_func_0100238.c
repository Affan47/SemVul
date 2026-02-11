create_city_map(struct city *pCity)
{


  if (city_map_canvas) {
    canvas_free(city_map_canvas);
  }

  city_map_canvas = canvas_create(get_citydlg_canvas_width(),
                                  get_citydlg_canvas_height());

  city_dialog_redraw_map(pCity, city_map_canvas);

  return city_map_canvas->surf;
}
