driver_close_device( void *driver_data )
{
     X11InputData *data   = driver_data;
     DFBX11       *x11    = data->x11;
     DFBX11Shared *shared = x11->shared;


     data->stop = true;

     XLockDisplay( x11->display );

     if (shared->xw) {
          XWindow *xw = shared->xw;

          shared->xw = NULL;


          dfb_x11_close_window( x11, xw );
     }

     XSync( x11->display, False );

     XUnlockDisplay( x11->display );


     if (data->thread != direct_thread_self()) {
          direct_thread_join( data->thread );
          direct_thread_destroy( data->thread );
     }


     D_FREE ( data );
}
