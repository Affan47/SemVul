nemo_icon_container_set_tighter_layout (NemoIconContainer *container,
                                        gboolean tighter_layout)
{
   g_return_if_fail (NEMO_IS_ICON_CONTAINER (container));
   g_return_if_fail (tighter_layout == FALSE || tighter_layout == TRUE);
   if (container->details->tighter_layout == tighter_layout) {
       return;
   }

   container->details->tighter_layout = tighter_layout;

   if (container->details->auto_layout) {
       invalidate_label_sizes (container);
       redo_layout (container);

       g_signal_emit (container, signals[LAYOUT_CHANGED], 0);
   } else {


       invalidate_label_sizes (container);
       nemo_icon_container_request_update_all (container);
   }
}
