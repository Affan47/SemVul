elm_scroller_region_bring_in(Evas_Object *obj,
                             Evas_Coord x,
                             Evas_Coord y,
                             Evas_Coord w,
                             Evas_Coord h)
{
   ELM_SCROLLABLE_CHECK(obj);

   s_iface->region_bring_in(obj, x, y, w, h);
}
