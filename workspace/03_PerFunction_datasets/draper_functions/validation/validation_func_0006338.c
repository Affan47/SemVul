sm_new_owner(const char *fname, int lineno, char *buf)
{
   buf -= HEAD_SIZE;
   ((struct abufhead *)buf)->abfname = bufimode ? NULL : fname;
   ((struct abufhead *)buf)->ablineno = (uint32_t) lineno;
   ((struct abufhead *)buf)->abin_use = true;
   return;
}
