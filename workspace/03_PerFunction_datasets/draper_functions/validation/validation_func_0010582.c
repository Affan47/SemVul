_elm_map_pan_smart_calculate(Evas_Object *obj)
{
   Evas_Coord w, h;

   ELM_MAP_PAN_DATA_GET(obj, psd);

   evas_object_geometry_get(obj, NULL, NULL, &w, &h);
   if (w <= 0 || h <= 0) return;

   _grid_place(psd->wsd);
   _overlay_place(psd->wsd);
   _track_place(psd->wsd);
   _delayed_do(psd->wsd);
}
