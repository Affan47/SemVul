evas_object_render_pre_clipper_change(Eina_Array *rects, Evas_Object *obj)
{
   if (obj->smart.smart) return;
   if (obj->cur.clipper == obj->prev.clipper) return;
   if ((obj->cur.clipper) && (obj->prev.clipper))
     {

        evas_rects_return_difference_rects(rects,
                                           obj->cur.clipper->cur.cache.clip.x,
                                           obj->cur.clipper->cur.cache.clip.y,
                                           obj->cur.clipper->cur.cache.clip.w,
                                           obj->cur.clipper->cur.cache.clip.h,
                                           obj->prev.clipper->prev.cache.clip.x,
                                           obj->prev.clipper->prev.cache.clip.y,
                                           obj->prev.clipper->prev.cache.clip.w,
                                           obj->prev.clipper->prev.cache.clip.h);
     }
   else if (obj->cur.clipper)
     {
        evas_rects_return_difference_rects(rects,
                                           obj->cur.geometry.x,
                                           obj->cur.geometry.y,
                                           obj->cur.geometry.w,
                                           obj->cur.geometry.h,


                                           obj->cur.clipper->cur.cache.clip.x,
                                           obj->cur.clipper->cur.cache.clip.y,
                                           obj->cur.clipper->cur.cache.clip.w,
                                           obj->cur.clipper->cur.cache.clip.h);
     }
   else if (obj->prev.clipper)
     {
     evas_rects_return_difference_rects(rects,
                                        obj->prev.geometry.x,
                                        obj->prev.geometry.y,
                                        obj->prev.geometry.w,
                                        obj->prev.geometry.h,


                                        obj->prev.clipper->prev.cache.clip.x,
                                        obj->prev.clipper->prev.cache.clip.y,
                                        obj->prev.clipper->prev.cache.clip.w,
                                        obj->prev.clipper->prev.cache.clip.h);
     }
}
