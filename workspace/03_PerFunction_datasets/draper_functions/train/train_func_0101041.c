_item_sub_items_clear(Elm_Gen_Item *it)
{
   Eina_List *tl = NULL, *l;
   Elm_Object_Item *it2;

   ELM_GENLIST_ITEM_CHECK_OR_RETURN(it);

   EINA_LIST_FOREACH (it->item->items, l, it2)
     tl = eina_list_append(tl, it2);
   EINA_LIST_FREE (tl, it2)
     elm_object_item_del(it2);
}
