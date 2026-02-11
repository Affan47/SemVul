elm_smart_scroller_gravity_set(Evas_Object *obj, double x, double y)
{
   API_ENTRY return;

   sd->pan_func.gravity_set(sd->pan_obj, x, y);
}
