elm_hover_parent_set(Evas_Object *obj,
                     Evas_Object *parent)
{
   ELM_HOVER_CHECK(obj);
   ELM_HOVER_DATA_GET(obj, sd);

   _elm_hover_parent_detach(obj);

   sd->parent = parent;
   if (sd->parent)
     {
        evas_object_event_callback_add
          (sd->parent, EVAS_CALLBACK_MOVE, _parent_move_cb, obj);
        evas_object_event_callback_add
          (sd->parent, EVAS_CALLBACK_RESIZE, _parent_resize_cb, obj);
        evas_object_event_callback_add
          (sd->parent, EVAS_CALLBACK_SHOW, _parent_show_cb, obj);
        evas_object_event_callback_add
          (sd->parent, EVAS_CALLBACK_HIDE, _parent_hide_cb, obj);
        evas_object_event_callback_add
          (sd->parent, EVAS_CALLBACK_DEL, _parent_del_cb, obj);
     }

   elm_layout_sizing_eval(obj);
}
