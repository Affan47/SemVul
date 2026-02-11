dfb_fbdev_pan( int xoffset, int yoffset, bool onsync )
{

     int                       result;
     struct fb_var_screeninfo *var;
     FBDevShared              *shared = dfb_fbdev->shared;

     if (!shared->fix.xpanstep && !shared->fix.ypanstep && !shared->fix.ywrapstep)
          return DFB_OK;

     var = &shared->current_var;

     if (var->xres_virtual < xoffset + var->xres) {
          D_ERROR( "DirectFB/FBDev: xres %d, vxres %d, xoffset %d\n",
                    var->xres, var->xres_virtual, xoffset );
          D_BUG( "panning buffer out of range" );
          return DFB_BUG;
     }

     if (var->yres_virtual < yoffset + var->yres) {
          D_ERROR( "DirectFB/FBDev: yres %d, vyres %d, offset %d\n",
                    var->yres, var->yres_virtual, yoffset );
          D_BUG( "panning buffer out of range" );
          return DFB_BUG;
     }

     if (shared->fix.xpanstep)
          var->xoffset = xoffset - (xoffset % shared->fix.xpanstep);
     else
          var->xoffset = 0;

     if (shared->fix.ywrapstep) {
          var->yoffset = yoffset - (yoffset % shared->fix.ywrapstep);
          var->vmode |= FB_VMODE_YWRAP;
     }
     else if (shared->fix.ypanstep) {
          var->yoffset = yoffset - (yoffset % shared->fix.ypanstep);
          var->vmode &= ~FB_VMODE_YWRAP;
     }
     else {
          var->yoffset = 0;
     }

     var->activate = onsync ? FB_ACTIVATE_VBL : FB_ACTIVATE_NOW;

#if 0
     ret = fusion_call_execute( &shared->fbdev_ioctl, FCEF_NONE, FBIOPAN_DISPLAY, var, &result );
     if (ret)
          return DFB_FUSION;

     if (result) {
          errno = result;
#else
     if (ioctl( dfb_fbdev->fd, FBIOPAN_DISPLAY, var ) < 0) {
          result = errno;
#endif
          D_PERROR( "DirectFB/FBDev: Panning display failed (x=%u y=%u ywrap=%d vbl=%d)!\n",
                    var->xoffset, var->yoffset,
                    (var->vmode & FB_VMODE_YWRAP) ? 1 : 0,
                    (var->activate & FB_ACTIVATE_VBL) ? 1 : 0);

          return errno2result(result);
     }

     return DFB_OK;
}
