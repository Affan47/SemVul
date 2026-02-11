ReadReply(mud_channel *pc)
{
   char buf[HPMUD_LINE_SIZE];
   int len=0, num=0;
   char *tail;
   enum HPMUD_RESULT stat;

   stat = jd_s_channel_read(pc, buf, sizeof(buf), 2, &len);
   buf[len] = 0;

   if (stat == HPMUD_R_OK)
      num = strtol((char *)buf, &tail, 10);

   return num;
}
