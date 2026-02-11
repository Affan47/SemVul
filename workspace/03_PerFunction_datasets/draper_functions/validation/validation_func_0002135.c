_item_disable_hook(Elm_Object_Item *it)
{
   Elm_List_Item *item = (Elm_List_Item *)it;

   if (item->base.disabled)
     edje_object_signal_emit(VIEW(item), "elm,state,disabled", "elm");
   else
     edje_object_signal_emit(VIEW(item), "elm,state,enabled", "elm");
}
