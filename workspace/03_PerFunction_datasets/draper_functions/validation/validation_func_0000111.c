evas_object_event_callback_cleanup(Evas_Object *obj)
{

   if (!obj->callbacks) return;
   evas_event_callback_list_post_free(&obj->callbacks->callbacks);
   EVAS_MEMPOOL_FREE(_mp_cb, obj->callbacks);
   obj->callbacks = NULL;
}
