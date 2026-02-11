_sizing_eval(Evas_Object *obj)
{
   Evas_Coord minw = -1, minh = -1, maxw = -1, maxh = -1;
   double scale;

   ELM_PHOTO_DATA_GET(obj, sd);

   if (sd->size <= 0) return;

   scale = (sd->size * elm_widget_scale_get(obj) * elm_config_scale_get());

   evas_object_size_hint_min_set(sd->icon, scale, scale);
   elm_coords_finger_size_adjust(1, &minw, 1, &minh);
   edje_object_size_min_restricted_calc
     (ELM_WIDGET_DATA(sd)->resize_obj, &minw, &minh, minw, minh);
   elm_coords_finger_size_adjust(1, &minw, 1, &minh);
   maxw = minw;
   maxh = minh;
   evas_object_size_hint_min_set(obj, minw, minh);
   evas_object_size_hint_max_set(obj, maxw, maxh);
}
