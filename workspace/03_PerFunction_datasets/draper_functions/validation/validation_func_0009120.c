FLASH_WaitForLastOperation(void)
{
  __IO FLASH_Status status = FLASH_COMPLETE;


  status = FLASH_GetStatus();


  while(status == FLASH_BUSY)
  {
    status = FLASH_GetStatus();
  }

  return status;
}
