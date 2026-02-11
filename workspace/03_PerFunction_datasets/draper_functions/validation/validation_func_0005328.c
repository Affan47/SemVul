evas_object_image_free(Evas_Object *obj)
{
   Evas_Object_Image *o;
   Eina_Rectangle *r;


   o = (Evas_Object_Image *)(obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Image, MAGIC_OBJ_IMAGE);
   return;
   MAGIC_CHECK_END();

   _cleanup_tmpf(obj);
   if (o->cur.file) eina_stringshare_del(o->cur.file);
   if (o->cur.key) eina_stringshare_del(o->cur.key);
   if (o->cur.source) _proxy_unset(obj);
   if (o->engine_data)
     {
        if (o->preloading)
          {
             o->preloading = 0;
             obj->layer->evas->engine.func->image_data_preload_cancel(obj->layer->evas->engine.data.output,
                                                                      o->engine_data,
                                                                      obj);
          }
        obj->layer->evas->engine.func->image_free(obj->layer->evas->engine.data.output,
                                                  o->engine_data);
     }
   if (o->video_surface)
     {
        o->video_surface = 0;
	obj->layer->evas->video_objects = eina_list_remove(obj->layer->evas->video_objects, obj);
     }
   o->engine_data = NULL;
   o->magic = 0;
   EINA_LIST_FREE(o->pixel_updates, r)
     eina_rectangle_free(r);
   EVAS_MEMPOOL_FREE(_mp_obj, o);
}
