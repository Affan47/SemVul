AaffDestroyHandle (t_pAaff *ppAaff)
{
   t_pAaff pAaff = *ppAaff;

   if (pAaff->pUncompressBuffer)
      free (pAaff->pUncompressBuffer);

   delete pAaff->pFilename;

   memset (pAaff, 0, sizeof(t_Aaff));
   UTIL_MEM_FREE (pAaff);
   *ppAaff = NULL;

   return NO_ERROR;
}
