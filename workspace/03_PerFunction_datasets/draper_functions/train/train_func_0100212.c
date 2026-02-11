_e_wid_disable_hook(Evas_Object *obj)
{
   E_Widget_Data *wd;

   wd = e_widget_data_get(obj);
   if (e_widget_disabled_get(obj))
     edje_object_signal_emit(wd->o_button, "e,state,disabled", "e");
   else
     edje_object_signal_emit(wd->o_button, "e,state,enabled", "e");
}
