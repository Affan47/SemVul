x_window_close_page (GSCHEM_TOPLEVEL *w_current, PAGE *page)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  PAGE *new_current = NULL;
  GList *iter;

  g_return_if_fail (toplevel != NULL);
  g_return_if_fail (page     != NULL);

  g_assert (page->pid != -1);


  if (w_current->inside_action &&
      (w_current->event_state == MOVE ||
       w_current->event_state == ENDMOVE)) {
    o_move_cancel (w_current);
  }

  if (page == toplevel->page_current) {


    new_current = s_page_search_by_page_id (toplevel->pages, page->up);

    if (new_current == NULL) {

      iter = g_list_find( geda_list_get_glist( toplevel->pages ), page );

      if ( g_list_previous( iter ) ) {
        new_current = (PAGE *)g_list_previous( iter )->data;
      } else if ( g_list_next( iter ) ) {
        new_current = (PAGE *)g_list_next( iter )->data;
      } else {

        new_current = NULL;
      }
    }

  }

  s_log_message (page->CHANGED ?
                 _("Discarding page [%s]\n") : _("Closing [%s]\n"),
                 page->page_filename);

  s_page_delete (toplevel, page);


  if (toplevel->page_current == NULL) {


    if (new_current == NULL) {
      new_current = x_window_open_page (w_current, NULL);
    }


    x_window_set_current_page (w_current, new_current);
  }
}
