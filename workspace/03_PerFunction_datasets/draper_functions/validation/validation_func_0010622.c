switch_focus( CoreWindowStack *stack,
              StackData       *data,
              CoreWindow      *to )
{
     DFBWindowEvent  evt;
     CoreWindow     *from;

     D_ASSERT( stack != NULL );
     D_ASSERT( data != NULL );

     from = data->focused_window;

     if (from == to)
          return;

     if (to && to->caps & DWCAPS_NOFOCUS)
          return;

     if (from) {
          evt.type = DWET_LOSTFOCUS;

          post_event( from, data, &evt );
     }

     if (to) {
          if (to->surface && to->surface->palette && !stack->hw_mode) {
               CoreSurface *surface;

               D_ASSERT( to->primary_region != NULL );

               if (dfb_layer_region_get_surface( to->primary_region, &surface ) == DFB_OK) {
                    if (DFB_PIXELFORMAT_IS_INDEXED( surface->config.format ))
                         dfb_surface_set_palette( surface, to->surface->palette );

                    dfb_surface_unref( surface );
               }
          }

          evt.type = DWET_GOTFOCUS;

          post_event( to, data, &evt );
     }

     data->focused_window = to;
}
