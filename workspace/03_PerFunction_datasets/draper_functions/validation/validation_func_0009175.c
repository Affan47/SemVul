dots_dialog_event(zdialog * zd, cchar *event)
{
   if (zd->zstat)
   {
      if (zd->zstat == 1) edit_done(EFdots);
      else edit_cancel(EFdots);
      return 0;
   }

   if (strEqu(event,"undo")) edit_undo();
   if (strEqu(event,"redo")) edit_redo();
   if (strEqu(event,"blendwidth")) signal_thread();
   if (strNeq(event,"apply")) return 0;

   zdialog_fetch(zd,"size",dot_size);
   signal_thread();
   return 1;
}
