_elm_grid_smart_focus_direction(const Evas_Object *obj,
                                const Evas_Object *base,
                                double degree,
                                Evas_Object **direction,
                                double *weight)
{
   Eina_Bool ret;
   const Eina_List *items;
   Eina_List *(*list_free)(Eina_List *list);
   void *(*list_data_get)(const Eina_List *list);

   ELM_GRID_DATA_GET(obj, sd);


   if ((items = elm_widget_focus_custom_chain_get(obj)))
     {
        list_data_get = eina_list_data_get;
        list_free = NULL;
     }
   else
     {
        items = evas_object_grid_children_get(ELM_WIDGET_DATA(sd)->resize_obj);
        list_data_get = eina_list_data_get;
        list_free = eina_list_free;

        if (!items) return EINA_FALSE;
     }

   ret = elm_widget_focus_list_direction_get(obj, base, items, list_data_get,
                                             degree, direction, weight);

   if (list_free) list_free((Eina_List *)items);

   return ret;
}
