_layout_change_cb(void *data, Evas_Object *obj __UNUSED__,
                  const char *emission __UNUSED__,
                  const char *source __UNUSED__)
{
   Widget_Data *wd = elm_widget_data_get((Evas_Object*)data);

   if (!wd) return;
   if (wd->base)
     elm_layout_sizing_eval(wd->base);
}
