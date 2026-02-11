update_stats(UAContext *ua)
{
   int i = find_arg_with_value(ua, NT_("days"));
   utime_t since=0;

   if (i >= 0) {
      since = atoi(ua->argv[i]) * 24*60*60;
   }

   int nb = db_update_stats(ua->jcr, ua->db, since);
   ua->info_msg(_("Updating %i job(s).\n"), nb);

   return true;
}
