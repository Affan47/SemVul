_item_new(Evas_Object *obj,
          const Elm_Naviframe_Item *prev_it,
          const char *title_label,
          Evas_Object *prev_btn,
          Evas_Object *next_btn,
          Evas_Object *content,
          const char *item_style)
{
   Elm_Naviframe_Item *it;

   ELM_NAVIFRAME_DATA_GET(obj, sd);

   it = elm_widget_item_new(obj, Elm_Naviframe_Item);
   if (!it)
     {
        ERR("Failed to allocate new item! : naviframe=%p", obj);
        return NULL;
     }

   elm_widget_item_del_pre_hook_set(it, _item_del_pre_hook);
   elm_widget_item_text_set_hook_set(it, _item_text_set_hook);
   elm_widget_item_text_get_hook_set(it, _item_text_get_hook);
   elm_widget_item_content_set_hook_set(it, _item_content_set_hook);
   elm_widget_item_content_get_hook_set(it, _item_content_get_hook);
   elm_widget_item_content_unset_hook_set(it, _item_content_unset_hook);
   elm_widget_item_signal_emit_hook_set(it, _item_signal_emit_hook);


   VIEW(it) = edje_object_add(evas_object_evas_get(obj));
   evas_object_smart_member_add(VIEW(it), obj);

   evas_object_event_callback_add
     (VIEW(it), EVAS_CALLBACK_CHANGED_SIZE_HINTS,
     _on_item_size_hints_changed, obj);
   edje_object_signal_callback_add
     (VIEW(it), "elm,action,show,finished", "", _on_item_show_finished, it);
   edje_object_signal_callback_add
     (VIEW(it), "elm,action,pushed,finished", "", _on_item_push_finished, it);
   edje_object_signal_callback_add
     (VIEW(it), "elm,action,popped,finished", "", _on_item_pop_finished, it);
   edje_object_signal_callback_add
     (VIEW(it), "elm,action,title,clicked", "", _on_item_title_clicked, it);

   _item_style_set(it, item_style);

   if (title_label)
     _item_text_set_hook((Elm_Object_Item *)it, "elm.text.title", title_label);


   if ((!prev_btn) && sd->auto_pushed && prev_it)
     {
        const char *prev_title = prev_it->title_label;
        prev_btn = _back_btn_new(obj, prev_title);
     }

   if (prev_btn)
     _item_content_set_hook((Elm_Object_Item *)it, PREV_BTN_PART, prev_btn);

   if (next_btn)
     _item_content_set_hook((Elm_Object_Item *)it, NEXT_BTN_PART, next_btn);

   _item_content_set(it, content);
   it->title_visible = EINA_TRUE;

   return it;
}
