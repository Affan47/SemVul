elm_gengrid_item_cursor_unset(Elm_Object_Item *item)
{
   Elm_Gen_Item *it = (Elm_Gen_Item *)item;

   ELM_GENGRID_ITEM_CHECK_OR_RETURN(it);
   if (!it->mouse_cursor)
     return;

   if (VIEW(it))
     elm_widget_item_cursor_unset(it);

   eina_stringshare_del(it->mouse_cursor);
   it->mouse_cursor = NULL;
}
