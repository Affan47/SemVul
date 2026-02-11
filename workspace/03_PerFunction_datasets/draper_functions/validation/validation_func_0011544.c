centry_list_init_double(lList *this_list)
{
   bool ret = true;

   DENTER(CENTRY_LAYER, "centry_list_init_double");
   if (this_list != NULL) {
      lListElem *centry;

      for_each(centry, this_list) {
         double new_val = 0.0;


         parse_ulong_val(&new_val, NULL, lGetUlong(centry, CE_valtype),
                         lGetString(centry, CE_stringval), NULL, 0);
         lSetDouble(centry, CE_doubleval, new_val);
      }
   }
   DRETURN(ret);
}
