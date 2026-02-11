elm_widget_signal_callback_del(Evas_Object *obj,
                               const char *emission,
                               const char *source,
                               Edje_Signal_Cb func)
{
   Edje_Signal_Data *esd;
   Eina_List *l;
   void *data = NULL;
   API_ENTRY return NULL;

   if (_elm_legacy_is(obj))
     {
        if (!COMPAT_SMART_DATA(sd)->callback_del) return NULL;

        EINA_LIST_FOREACH (COMPAT_SMART_DATA(sd)->edje_signals, l, esd)
          {
             if ((esd->func == func) && (!strcmp(esd->emission, emission)) &&
                 (!strcmp(esd->source, source)))
               {
                  COMPAT_SMART_DATA(sd)->edje_signals = eina_list_remove_list
                      (COMPAT_SMART_DATA(sd)->edje_signals, l);
                  eina_stringshare_del(esd->emission);
                  eina_stringshare_del(esd->source);
                  data = esd->data;
                  free(esd);
                  break;
               }
          }

        COMPAT_SMART_DATA(sd)->callback_del
          (obj, emission, source, _edje_signal_callback, esd);
     }
   else if (evas_object_smart_type_check(obj, "elm_layout"))
     data = elm_layout_signal_callback_del(obj, emission, source, func);
   else if (evas_object_smart_type_check(obj, "elm_icon"))
     {
        WRN("Deprecated function. This functionality on icon objects"
            " will be dropped on a next release.");

        data = _elm_icon_signal_callback_del(obj, emission, source, func);
     }

   return data;
}
