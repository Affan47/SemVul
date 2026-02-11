_e_winlist_deactivate(void)
{
   E_Winlist_Win *ww;

   if (!_win_selected) return;
   ww = _win_selected->data;
   if (ww->was_shaded)
     {
        if (!ww->border->lock_user_shade)
          e_border_shade(ww->border, ww->border->shade.dir);
     }
   if (ww->was_iconified)
     {
        if (!ww->border->lock_user_iconify)
          e_border_iconify(ww->border);
     }
   ww->was_shaded = 0;
   ww->was_iconified = 0;
   if (_icon_object)
     {
        evas_object_del(_icon_object);
        _icon_object = NULL;
     }
   edje_object_part_text_set(_bg_object, "e.text.label", "");
   edje_object_signal_emit(ww->bg_object, "e,state,unselected", "e");
   if (ww->icon_object)
     edje_object_signal_emit(ww->icon_object,
                             "e,state,unselected", "e");
   if (!ww->border->lock_focus_in)
     e_border_focus_set(ww->border, 0, 0);
}
