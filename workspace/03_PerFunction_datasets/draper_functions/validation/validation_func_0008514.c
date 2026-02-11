get_rsrc(const char *name, bool queue, int *field, int *cqfld, int *valfld, int *type)
{
   int pos = 0;
   const struct queue2cmplx *rlist;
   int nitems;

   if (queue) {
      rlist = &queue_resource[0];
      nitems = max_queue_resources;
   } else {
      rlist = &host_resource[0];
      nitems = max_host_resources;
   }

   for (; pos < nitems; pos++) {
      if (strcmp(name, rlist[pos].name) == 0) {
         if (field) *field = rlist[pos].field;
         if (cqfld) *cqfld = rlist[pos].cqfld;
         if (valfld) *valfld = rlist[pos].valfld;
         if (type) *type = rlist[pos].type;
         return 0;
      }
   }

   return -1;
}
