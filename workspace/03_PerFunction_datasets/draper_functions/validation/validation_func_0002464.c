cqueue_sick(lListElem *cqueue, lList **answer_list,
            lList *master_hgroup_list, dstring *ds)
{
   bool ret = true;

   DENTER(TOP_LAYER, "cqueue_sick");


   {
      const char *cqueue_name = lGetString(cqueue, CQ_name);
      lList *used_hosts = NULL;
      lList *used_groups = NULL;
      lList **answer_list = NULL;
      int index;


      href_list_find_all_references(lGetList(cqueue, CQ_hostlist), answer_list,
                                    master_hgroup_list, &used_hosts,
                                    &used_groups);

      index = 0;
      while (cqueue_attribute_array[index].cqueue_attr != NoName) {


         lList *attr_list = lGetList(cqueue,
                                 cqueue_attribute_array[index].cqueue_attr);
         lListElem *next_attr = lFirst(attr_list);
         lListElem *attr = NULL;


         while((attr = next_attr) != NULL) {
            const char *name = lGetHost(attr,
                                   cqueue_attribute_array[index].href_attr);

            next_attr = lNext(attr);
            if (is_hgroup_name(name)) {
               if (strcmp(name, HOSTREF_DEFAULT)) {
                  lListElem *hgroup = NULL;
                  lList *used_hgroup_hosts = NULL;
                  lList *used_hgroup_groups = NULL;
                  lList *add_hosts = NULL;
                  lList *equity_hosts = NULL;

                  hgroup = hgroup_list_locate(master_hgroup_list, name);


                  hgroup_find_all_references(hgroup, answer_list,
                                             master_hgroup_list,
                                             &used_hgroup_hosts,
                                             &used_hgroup_groups);
                  href_list_compare(used_hgroup_hosts, answer_list,
                                    used_hosts, &add_hosts, NULL,
                                    &equity_hosts, NULL);

                  if (lGetNumberOfElem(add_hosts)) {
                     DTRACE;
                     sge_dstring_sprintf_append(ds,
                             MSG_CQUEUE_DEFOVERWRITTEN_SSSSS,
                             cqueue_attribute_array[index].name,
                             name, cqueue_name, name, cqueue_name);
                     sge_dstring_append(ds, "\n");
                  }

                  lFreeList(&add_hosts);
                  lFreeList(&equity_hosts);
                  lFreeList(&used_hgroup_hosts);
                  lFreeList(&used_hgroup_groups);
               } else {
                  DTRACE;
               }
            } else {


               if (!href_list_has_member(used_hosts, name)) {
                  DTRACE;
                  sge_dstring_sprintf_append(ds,
                             MSG_CQUEUE_UNUSEDATTRSETTING_SS,
                             cqueue_attribute_array[index].name,
                             name, cqueue_name);
                  sge_dstring_append(ds, "\n");
               } else {
                  DTRACE;
               }
            }
         }

         index++;
      }
      lFreeList(&used_hosts);
      lFreeList(&used_groups);
   }

   DRETURN(ret);
}
