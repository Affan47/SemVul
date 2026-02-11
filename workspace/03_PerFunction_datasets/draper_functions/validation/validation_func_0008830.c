_elm_bg_smart_add(Evas_Object *obj)
{
   EVAS_SMART_DATA_ALLOC(obj, Elm_Bg_Smart_Data);

   ELM_WIDGET_CLASS(_elm_bg_parent_sc)->base.add(obj);

   elm_widget_can_focus_set(obj, EINA_FALSE);

   priv->option = ELM_BG_OPTION_SCALE;

   evas_object_event_callback_add(obj, EVAS_CALLBACK_RESIZE, _on_resize, obj);

   elm_layout_theme_set(obj, "bg", "base", elm_widget_style_get(obj));
}
