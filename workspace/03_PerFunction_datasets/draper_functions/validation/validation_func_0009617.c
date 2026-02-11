DeleteConf(ConfServer *pCS)
{
   LOG_NORM(("Deleting conference for port %d.\n",pCS->AudioPort));
   if(avl_delete(Conferences,pCS) == NULL) {
      LOG_ERROR(("DeleteConf: avl_delete() failed to find client.\n"));
   }

   if(pCS->pAudio != NULL) {
      pCS->pAudio->p = NULL;
      DeleteClient(pCS->pAudio);
   }

   if(pCS->pControl != NULL) {
      pCS->pControl->p = NULL;
      DeleteClient(pCS->pControl);
   }

   if(pCS->fp != NULL) {
      fclose(pCS->fp);
   }

   if(!pCS->bSlaveConf && pCS->ConfTree != NULL) {
      avl_destroy(pCS->ConfTree,NULL);
   }

   free(pCS);
}
