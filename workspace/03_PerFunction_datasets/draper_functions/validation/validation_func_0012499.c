elm_toolbar_first_item_get(const Evas_Object *obj)
{
   ELM_CHECK_WIDTYPE(obj, widtype) NULL;
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd || !wd->items) return NULL;
   return (Elm_Object_Item *) ELM_TOOLBAR_ITEM_FROM_INLIST(wd->items);
}
