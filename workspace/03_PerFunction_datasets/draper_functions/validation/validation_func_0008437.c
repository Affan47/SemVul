jd_get_device_id(mud_device *pd, char *buf, int size, int *len)
{
   enum HPMUD_RESULT stat = HPMUD_R_IO_ERROR;

   *len=0;

   pthread_mutex_lock(&pd->mutex);

   *len = device_id(pd->ip, pd->port, pd->id, sizeof(pd->id));

   if (*len)
   {
      memcpy(buf, pd->id, *len > size ? size : *len);
      stat = HPMUD_R_OK;
   }

   pthread_mutex_unlock(&pd->mutex);
   return stat;
}
