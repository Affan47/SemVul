dfb_window_destroy( CoreWindow *window )
{
     DFBWindowEvent   evt;
     CoreWindowStack *stack;
     BoundWindow     *bound, *next;

     D_ASSERT( window != NULL );
     D_ASSERT( DFB_WINDOW_INITIALIZED( window ) );

     D_DEBUG_AT( Core_Windows, "dfb_window_destroy (%p) [%4d,%4d - %4dx%4d]\n",
                 window, DFB_RECTANGLE_VALS( &window->config.bounds ) );

     D_ASSUME( window->stack != NULL );

     stack = window->stack;
     if (!stack)
          return;


     if (dfb_windowstack_lock( stack ))
          return;


     if (DFB_WINDOW_DESTROYED( window )) {
          D_DEBUG_AT( Core_Windows, "%p already destroyed.\n", window );
          dfb_windowstack_unlock( stack );
          return;
     }


     direct_list_foreach_safe (bound, next, window->bound_windows) {
          direct_list_remove( &window->bound_windows, &bound->link );

          bound->window->boundto = NULL;

          SHFREE( stack->shmpool, bound );
     }


     if (window->boundto)
          dfb_window_unbind( window->boundto, window );


     dfb_window_set_opacity( window, 0 );


     dfb_wm_remove_window( stack, window );


     D_FLAGS_SET( window->flags, CWF_DESTROYED );


     if (window->region) {

          dfb_layer_region_disable( window->region );


          dfb_layer_region_unlink( &window->region );
     }


     if (window->surface) {
          dfb_surface_unlink( &window->surface );
     }


     stack->num--;


     dfb_windowstack_unlock( stack );


     evt.type = DWET_DESTROYED;
     dfb_window_post_event( window, &evt );
}
