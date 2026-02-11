sa_finish_dialog_event(zdialog *zd, cchar *event)
{
   int         zstat;

   zstat = zd->zstat;
   if (! zstat) return 0;

   freeMouse();
   zdialog_free(safinzd);

   if (! sa_stat) return 0;

   if (zstat != 1 || sa_finOK == 0 || sa_finhole) {
      sa_unfinish();
      return 0;
   }

   sa_map_pixels();

   sa_stat = 3;
   Factivearea = 1;
   areanumber++;
   sa_calced = sa_blend = 0;
   if (zdsela) zdialog_stuff(zdsela,"blendwidth",0);
   mwpaint2();
   return 0;
}
