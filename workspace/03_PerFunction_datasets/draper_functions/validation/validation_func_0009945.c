_elm_ews_border_focus_apply(Ecore_Evas *ee, Evas_Object *o)
{
   const char *sig;
   if (ecore_evas_focus_get(ee))
     sig = "elm,state,focus,on";
   else
     sig = "elm,state,focus,off";
   edje_object_signal_emit(o, sig, "elm");
}
