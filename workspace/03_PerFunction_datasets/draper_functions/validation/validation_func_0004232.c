job_get_wallclock_limit(u_long32 *limit, const lListElem *jep) {
   lListElem *ep;
   double d_ret = 0, d_tmp;
   const char *s;
   bool got_duration = false;
   char error_str[1024];

   DENTER(TOP_LAYER, "job_get_wallclock_limit");

   if ((ep=lGetElemStr(lGetList(jep, JB_hard_resource_list), CE_name, SGE_ATTR_H_RT))) {
      if (parse_ulong_val(&d_tmp, NULL, TYPE_TIM, (s=lGetString(ep, CE_stringval)),
               error_str, sizeof(error_str)-1)==0) {
         ERROR((SGE_EVENT, MSG_CPLX_WRONGTYPE_SSS, SGE_ATTR_H_RT, s, error_str));
         DRETURN(false);
      }
      d_ret = d_tmp;
      got_duration = true;
   }

   if ((ep=lGetElemStr(lGetList(jep, JB_hard_resource_list), CE_name, SGE_ATTR_S_RT))) {
      if (parse_ulong_val(&d_tmp, NULL, TYPE_TIM, (s=lGetString(ep, CE_stringval)),
               error_str, sizeof(error_str)-1)==0) {
         ERROR((SGE_EVENT, MSG_CPLX_WRONGTYPE_SSS, SGE_ATTR_H_RT, s, error_str));
         DRETURN(false);
      }

      if (got_duration) {
         d_ret = MIN(d_ret, d_tmp);
      } else {
         d_ret = d_tmp;
         got_duration = true;
      }
   }

   if (got_duration) {
      if (d_ret > (double)U_LONG32_MAX) {
         *limit = U_LONG32_MAX;
      } else {
         *limit = d_ret;
      }
   } else {
      *limit = U_LONG32_MAX;
   }

   DRETURN(got_duration);
}
