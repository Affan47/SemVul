rqs_add(sge_gdi_ctx_class_t *ctx, lList **answer_list, const char *name)
{
   bool ret = false;

   DENTER(TOP_LAYER, "rqs_list_add");
   if (name != NULL) {
      lList *rqs_list = NULL;
      lListElem *rqs = NULL;

      lString2List(name, &rqs_list, RQS_Type, RQS_name, ", ");
      for_each (rqs, rqs_list) {
         rqs = rqs_set_defaults(rqs);
      }

      ret = rqs_provide_modify_context(ctx, &rqs_list, answer_list, true);

      if (ret) {
         ret = rqs_add_del_mod_via_gdi(ctx, rqs_list, answer_list, SGE_GDI_ADD | SGE_GDI_SET_ALL);
      }

      lFreeList(&rqs_list);
   }

   DRETURN(ret);
}
