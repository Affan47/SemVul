info_edit_dialog_event(zdialog *zd, cchar *event)
{
   char        keyname[40], keydata[1000];
   cchar       *pp1[1], *pp2[1];
   char        **pp3;
   int         err;

   if (! zd->zstat) return 0;

   zdialog_fetch(zd,"keyname",keyname,40);
   zdialog_fetch(zd,"keydata",keydata,1000);
   strCompress(keyname);

   if (zd->zstat == 1)
   {
      zd->zstat = 0;
      if (! *keyname) return 0;
      pp1[0] = keyname;
      pp3 = info_get(curr_file,pp1,1);
      if (pp3[0]) {
         strncpy0(keydata,pp3[0],99);
         zfree(pp3[0]);
      }
      else *keydata = 0;
      zdialog_stuff(zd,"keydata",keydata);
   }

   else if (zd->zstat == 2)
   {
      zd->zstat = 0;
      if (! *keyname) return 0;
      if (is_syncbusy()) return 0;
      pp1[0] = keyname;
      pp2[0] = keydata;
      err = info_put(curr_file,pp1,pp2,1);
      if (err) zmessageACK(mWin,"error: %s",strerror(err));
      if (zdexifview) info_view(0);
   }

   else zdialog_free(zdexifedit);

   return 1;
}
