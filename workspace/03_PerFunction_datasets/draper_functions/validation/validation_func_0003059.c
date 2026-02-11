_evry_selector_free(Evry_Selector *sel)
{
   Evry_Window *win = sel->win;

   _evry_selector_item_clear(sel);

   if (win->visible && (sel == CUR_SEL))
     _evry_view_clear(sel->state);

   while (sel->states)
     _evry_state_pop(sel, 1);

   EVRY_PLUGIN_FREE(sel->aggregator);

   if (sel->plugins) eina_list_free(sel->plugins);

   if (sel->update_timer)
     ecore_timer_del(sel->update_timer);

   if (sel->action_timer)
     ecore_timer_del(sel->action_timer);

   E_FREE(sel);
}
