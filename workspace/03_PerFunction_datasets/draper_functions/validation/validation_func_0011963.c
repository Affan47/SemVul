Gal_get_alpha_enable(int *enable)
{
   GAL_ALPHAENABLE sGetalphaenable;

   INIT_GAL(&sGetalphaenable);
   sGetalphaenable.dwSubfunction = GALFN_GETALPHAENABLE;

   if (ioctl(dfb_fbdev->fd, FBIOGAL_API, &sGetalphaenable))
      return 0;
   else

      *enable = sGetalphaenable.enable;
   return 1;
}
