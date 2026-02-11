_overlay_scale_new(Elm_Map_Smart_Data *sd,
                   Evas_Coord x,
                   Evas_Coord y,
                   Color c)
{
   const char *s;
   Overlay_Scale *ovl;

   ovl = ELM_NEW(Overlay_Scale);
   ovl->wsd = sd;
   ovl->x = x;
   ovl->y = y;

   ovl->obj = elm_layout_add(ELM_WIDGET_DATA(sd)->obj);
   evas_object_smart_member_add(ovl->obj, sd->pan_obj);
   evas_object_stack_above(ovl->obj, sd->sep_maps_overlays);
   elm_layout_theme_set(ovl->obj, "map/scale", "base",
                        elm_widget_style_get(ELM_WIDGET_DATA(sd)->obj));
   s = edje_object_data_get(elm_layout_edje_get(ovl->obj), "size_w");

   if (s) ovl->w = atoi(s);
   else ovl->w = 100;

   s = edje_object_data_get(elm_layout_edje_get(ovl->obj), "size_h");
   if (s) ovl->h = atoi(s);
   else ovl->h = 60;

   _overlay_scale_color_update(ovl, c);

   return ovl;
}
