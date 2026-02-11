fb_cleanup(void)
{

   if (ioctl(fb, FBIOPUT_VSCREENINFO, &fb_ovar) == -1)
      perror("ioctl FBIOPUT_VSCREENINFO");
   if (ioctl(fb, FBIOGET_FSCREENINFO, &fb_fix) == -1)
      perror("ioctl FBIOGET_FSCREENINFO");
   if ((fb_ovar.bits_per_pixel == 8) ||
       (fb_fix.visual == FB_VISUAL_DIRECTCOLOR))
     {
        if (ioctl(fb, FBIOPUTCMAP, &ocmap) == -1)
           perror("ioctl FBIOPUTCMAP");
     }
   close(fb);
   if (tty)
     {
	if (ioctl(tty, KDSETMODE, kd_mode) == -1)
           perror("ioctl KDSETMODE");
	if (ioctl(tty, VT_SETMODE, &vt_omode) == -1)
           perror("ioctl VT_SETMODE");
#if 0
	if ((ioctl(tty, VT_ACTIVATE, orig_vt_no) == -1) && (orig_vt_no))
           perror("ioctl VT_ACTIVATE");
#endif
     }
   close(tty);
}
