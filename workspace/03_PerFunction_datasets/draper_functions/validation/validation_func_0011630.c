scsi_enable_cdda (cdrom_drive *d, int fAudioMode){
  if (fAudioMode) {
    if(mode_select(d,d->density,CD_FRAMESIZE_RAW)){
      if(d->error_retry)
	cderror(d,"001: Unable to set CDROM to read audio mode\n");
      return(-1);
    }
  } else {
    if(mode_select(d,d->orgdens,d->orgsize)){
      if(d->error_retry)
	cderror(d,"001: Unable to set CDROM to read audio mode\n");
      return(-1);
    }
  }
  return(0);
}
