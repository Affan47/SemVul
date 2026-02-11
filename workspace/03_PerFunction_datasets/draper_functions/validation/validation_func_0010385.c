chunk_del(chunk_t *pc)
{
   g_cl.Pop(pc);
   if ((pc->flags & PCF_OWN_STR) && (pc->str != NULL))
   {
      delete[] (char *)pc->str;
      pc->str = NULL;
   }
   delete pc;
}
