_elm_notify_smart_theme(Evas_Object *obj)
{
   ELM_NOTIFY_DATA_GET(obj, sd);

   if (!ELM_WIDGET_CLASS(_elm_notify_parent_sc)->theme(obj)) return EINA_FALSE;

   _mirrored_set(obj, elm_widget_mirrored_get(obj));

   _notify_theme_apply(obj);
   if (sd->block_events) _block_events_theme_apply(obj);

   edje_object_scale_set
     (sd->notify, elm_widget_scale_get(obj) * elm_config_scale_get());

   _sizing_eval(obj);

   return EINA_TRUE;
}
