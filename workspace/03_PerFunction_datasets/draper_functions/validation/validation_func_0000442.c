sge_has_access_(const char *user, const char *group, const lList *q_acl,
                    const lList *q_xacl, const lList *acl_list)
{
   int ret;

   DENTER(TOP_LAYER, "sge_has_access_");

   ret = sge_contained_in_access_list_(user, group, q_xacl, acl_list);
   if (ret < 0 || ret == 1) {
      DRETURN(0);
   }

   if (!q_acl) {
       DRETURN(1);
   }

   ret = sge_contained_in_access_list_(user, group, q_acl, acl_list);
   if (ret < 0) {
      DRETURN(0);
   }
   if (ret) {

      DRETURN(1);
   }


   DRETURN(0);
}
