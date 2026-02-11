upd_open_fscmy_k(upd_device *udev)
{
   const upd_p upd = udev->upd;

   upd_open_fscomp(udev);

   if((B_RENDER & upd->flags) &&
      (4 == upd->ncomp)) {
      upd->render = upd_fscmy_k;
   } else {
      upd->flags &= ~B_RENDER;
   }

}
