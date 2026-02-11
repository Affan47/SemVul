InitLocal( DFBX11 *x11, DFBX11Shared *shared, CoreDFB *core )
{
     int i, n;

     XInitThreads();

     x11->shared = shared;
     x11->core   = core;

     x11->display = XOpenDisplay(getenv("DISPLAY"));
     if (!x11->display) {
          D_ERROR("X11: Error in XOpenDisplay for '%s'\n", getenv("DISPLAY"));
          return DFB_INIT;
     }

     x11->screenptr = DefaultScreenOfDisplay(x11->display);
     x11->screennum = DefaultScreen(x11->display);

     for (i=0; i<x11->screenptr->ndepths; i++) {
          const Depth *depth = &x11->screenptr->depths[i];

          for (n=0; n<depth->nvisuals; n++) {
               Visual *visual = &depth->visuals[n];

               D_DEBUG( "X11/Visual: [%2d] ID 0x%02lx, depth %d, red 0x%06lx, green 0x%06lx, blue 0x%06lx, %d bits/rgb, %d entries\n",
                        n, visual->visualid, depth->depth,
                        visual->red_mask, visual->green_mask, visual->blue_mask,
                        visual->bits_per_rgb, visual->map_entries );

               switch (depth->depth) {
                    case 32:
                         if (visual->red_mask   == 0xff0000 &&
                             visual->green_mask == 0x00ff00 &&
                             visual->blue_mask  == 0x0000ff &&
                             !x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_ARGB)])
                              x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_ARGB)] = visual;
                         break;

                    case 24:
                         if (visual->red_mask   == 0xff0000 &&
                             visual->green_mask == 0x00ff00 &&
                             visual->blue_mask  == 0x0000ff &&
                             !x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB32)])
                              x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB32)] = visual;
                         break;

                    case 16:
                         if (visual->red_mask   == 0xf800 &&
                             visual->green_mask == 0x07e0 &&
                             visual->blue_mask  == 0x001f &&
                             !x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB16)])
                              x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB16)] = visual;
                         break;

                    case 15:
                         if (visual->red_mask   == 0x7c00 &&
                             visual->green_mask == 0x03e0 &&
                             visual->blue_mask  == 0x001f &&
                             !x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB555)])
                              x11->visuals[DFB_PIXELFORMAT_INDEX(DSPF_RGB555)] = visual;
                         break;
               }
          }
     }

     if (XShmQueryExtension( x11->display ))
          XShmQueryVersion( x11->display, &x11->xshm_major, &x11->xshm_minor, &x11->use_shm );


     x11->screen = dfb_screens_register( NULL, x11, &x11PrimaryScreenFuncs );

     dfb_layers_register( x11->screen, x11, &x11PrimaryLayerFuncs );

     return DFB_OK;
}
