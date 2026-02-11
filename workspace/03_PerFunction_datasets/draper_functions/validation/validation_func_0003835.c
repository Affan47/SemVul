emboss_dialog_event(zdialog *zd, cchar *event)
{
   if (zd->zstat)
   {
      if (zd->zstat == 1) edit_done(EFemboss);
      else edit_cancel(EFemboss);
      return 0;
   }

   if (strEqu(event,"undo")) edit_undo();
   if (strEqu(event,"redo")) edit_redo();
   if (strEqu(event,"blendwidth")) signal_thread();

   if (strcmpv(event,"radius","depth","color",null))
   {
      zdialog_fetch(zd,"radius",emboss_radius);
      zdialog_fetch(zd,"depth",emboss_depth);
      zdialog_fetch(zd,"color",emboss_color);
      signal_thread();
   }

   return 1;
}
