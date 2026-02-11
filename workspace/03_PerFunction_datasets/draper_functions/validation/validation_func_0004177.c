elm_transit_object_remove(Elm_Transit *transit, Evas_Object *obj)
{
   ELM_TRANSIT_CHECK_OR_RETURN(transit);
   EINA_SAFETY_ON_NULL_RETURN(obj);

   _transit_obj_remove(transit, obj);
   if (!transit->objs) elm_transit_del(transit);
}
