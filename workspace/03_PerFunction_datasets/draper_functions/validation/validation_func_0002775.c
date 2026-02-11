elm_map_overlay_show(Elm_Map_Overlay *overlay)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   EINA_SAFETY_ON_NULL_RETURN(overlay);
   EINA_SAFETY_ON_NULL_RETURN(overlay->wsd);
   ELM_MAP_CHECK(ELM_WIDGET_DATA(overlay->wsd)->obj);

   if (overlay->type == ELM_MAP_OVERLAY_TYPE_DEFAULT)
     {
        Overlay_Default *ovl = overlay->ovl;

        elm_map_region_show
          (ELM_WIDGET_DATA(overlay->wsd)->obj, ovl->lon, ovl->lat);
     }
   else if (overlay->type == ELM_MAP_OVERLAY_TYPE_BUBBLE)
     {
        Overlay_Bubble *ovl = overlay->ovl;

        elm_map_region_show
          (ELM_WIDGET_DATA(overlay->wsd)->obj, ovl->lon, ovl->lat);
     }
   else if (overlay->type == ELM_MAP_OVERLAY_TYPE_CLASS)
     {
        Overlay_Class *ovl = overlay->ovl;
        double lon, lat, max_lo, min_lo, max_la, min_la;

        _region_max_min_get(ovl->members, &max_lo, &min_lo, &max_la, &min_la);
        lon = (max_lo + min_lo) / 2;
        lat = (max_la + min_la) / 2;
        elm_map_region_show(ELM_WIDGET_DATA(overlay->wsd)->obj, lon, lat);
     }
   else ERR("Not supported overlay type: %d", overlay->type);

   evas_object_smart_changed(overlay->wsd->pan_obj);
#else
   (void)overlay;
#endif
}
