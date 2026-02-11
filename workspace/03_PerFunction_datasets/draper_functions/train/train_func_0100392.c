sge_is_start_user_superuser(void)
{
   bool   is_root = false;
   uid_t  start_uid;

   DENTER(UIDGID_LAYER, "sge_is_start_user_superuser");

   start_uid = getuid();
   is_root = (start_uid == SGE_SUPERUSER_UID)?true:false;

   DEXIT;
   return is_root;
}
