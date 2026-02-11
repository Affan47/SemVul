_pager_popup_cb_mouse_down(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   Ecore_Event_Mouse_Button *ev;
   Pager_Popup *pp = act_popup;

   ev = event;
   if (ev->window != input_window) return ECORE_CALLBACK_PASS_ON;

   evas_event_feed_mouse_down(pp->popup->evas, ev->buttons,
                              0, ev->timestamp, NULL);
   return ECORE_CALLBACK_PASS_ON;
}
