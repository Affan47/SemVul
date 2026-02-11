system_leave( bool emergency )
{
     DFBX11       *x11    = dfb_system_data();
     DFBX11Shared *shared = x11->shared;


     if (shared->vpsmem_pool)
          dfb_surface_pool_leave( shared->vpsmem_pool );

     if (shared->x11image_pool)
          dfb_surface_pool_leave( shared->x11image_pool );


     if (x11->display)
         XCloseDisplay( x11->display );

     D_FREE( x11 );

     return DFB_OK;
}
