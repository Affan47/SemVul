execd_get_wallclock_limit(const char *qualified_hostname, lList *gdil_list, int limit_nm, u_long32 now)
{
   u_long32 ret = U_LONG32_MAX;
   const lListElem *gdil;
   const void *iterator;

   gdil = lGetElemHostFirst(gdil_list, JG_qhostname, qualified_hostname, &iterator);
   while (gdil != NULL) {
      const lListElem *queue;
      const char *limit;
      u_long32 clock_val;

      queue = lGetObject(gdil, JG_queue);
      if (queue != NULL) {
         limit = lGetString(queue, limit_nm);

         if (strcasecmp(limit, "infinity") == 0) {
            clock_val = U_LONG32_MAX;
         } else {
            parse_ulong_val(NULL, &clock_val, TYPE_TIM, limit, NULL, 0);
         }

         ret = MIN(ret, clock_val);
      }

      gdil = lGetElemHostNext(gdil_list, JG_qhostname, qualified_hostname, &iterator);
   }

   if (ret != U_LONG32_MAX) {
      ret += now;
   }

   return ret;
}
