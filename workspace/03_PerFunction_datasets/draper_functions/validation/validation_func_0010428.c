MediaIdentify (int fd, t_pMediaDriveCmd pDriveCmd)
{
   int i;

   memset(pDriveCmd, 0, sizeof(*pDriveCmd));
   pDriveCmd->Request.command      = ATA_OP_IDENTIFY;
   pDriveCmd->Request.sector_count = 1;
   if (do_drive_cmd(fd, (unsigned char *)pDriveCmd))
   {
      pDriveCmd->Request.command       = ATA_OP_PIDENTIFY;
      pDriveCmd->Request.sector_number = 0;
      pDriveCmd->Request.feature       = 0;
      pDriveCmd->Request.sector_count  = 1;
      if (do_drive_cmd (fd, (unsigned char *)pDriveCmd))
         return ERROR_MEDIA_IDENTIFY_FAILED;
   }

   for (i = 0; i < 0x100; ++i)
      __le16_to_cpus (&pDriveCmd->Result.Arr[i]);

   return NO_ERROR;
}
