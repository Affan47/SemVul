_size_list_load(E_Config_Dialog_Data *cfdata, Eina_List *size_list, Evas_Font_Size cur_size, int clear)
{
   Eina_List *next;
   Evas_Object *ob;
   Evas *evas;
   int n;

   ob = cfdata->gui.size_list;
   evas = evas_object_evas_get(ob);

   evas_event_freeze(evas);
   edje_freeze();
   e_widget_ilist_freeze(ob);
   if (clear) e_widget_ilist_clear(ob);

   for (next = size_list; next; next = next->next)
     {
        E_Font_Size_Data *size_data;

        size_data = next->data;
        e_widget_ilist_append(ob, NULL, size_data->size_str, _size_cb_change,
                              size_data, NULL);
     }

   e_widget_ilist_go(ob);
   e_widget_ilist_thaw(ob);
   edje_thaw();
   evas_event_thaw(evas);

   for (n = 0; n < e_widget_ilist_count(ob); n++)
     {
        E_Font_Size_Data *size_data;

        if (!(size_data = e_widget_ilist_nth_data_get(ob, n))) continue;
        if (cur_size == size_data->size)
          {
             e_widget_ilist_selected_set(ob, n);
             break;
          }
     }
}
