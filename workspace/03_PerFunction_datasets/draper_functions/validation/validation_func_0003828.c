odbc_clear_result_set(SV *sth, imp_sth_t *imp_sth)
{
   SV *value;
   char *key;
   I32 keylen;

   if (DBIc_TRACE(imp_sth, DBD_TRACING, 0, 3)) {
      TRACE0(imp_sth, "odbc_clear_result_set\n");
   }

   Safefree(imp_sth->fbh);
   Safefree(imp_sth->ColNames);
   Safefree(imp_sth->RowBuffer);


   if (DBIc_FIELDS_AV(imp_sth)) {
      sv_free((SV*)DBIc_FIELDS_AV(imp_sth));
      DBIc_FIELDS_AV(imp_sth) = Nullav;
   }

   while ( (value = hv_iternextsv((HV*)SvRV(sth), &key, &keylen)) ) {
      if (strncmp(key, "NAME_", 5) == 0 ||
	  strncmp(key, "TYPE", 4) == 0 ||
	  strncmp(key, "PRECISION", 9) == 0 ||
	  strncmp(key, "SCALE", 5) == 0 ||
	  strncmp(key, "NULLABLE", 8) == 0) {
          (void)hv_delete((HV*)SvRV(sth), key, keylen, G_DISCARD);
          if (DBIc_TRACE(imp_sth, DBD_TRACING, 0, 4)) {
              TRACE2(imp_sth, "    ODBC_CLEAR_RESULTS '%s' => %s\n",
                     key, neatsvpv(value,0));
          }
      }
   }

   imp_sth->fbh       = NULL;
   imp_sth->ColNames  = NULL;
   imp_sth->RowBuffer = NULL;
   imp_sth->done_desc = 0;
}
