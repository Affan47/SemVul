nemo_window_get_next_pane (NemoWindow *window)
{
       NemoWindowPane *next_pane;
       GList *node;


       if (!window->details->panes || !window->details->panes->next) {
	       return NULL;
       }


       node = g_list_find (window->details->panes, window->details->active_pane);
       g_return_val_if_fail (node, NULL);
       if (node->next) {
	       next_pane = node->next->data;
       } else {
	       next_pane =  window->details->panes->data;
       }

       return next_pane;
}
