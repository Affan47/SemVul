cull_mail(u_long32 progid, lList *user_list, const char *subj, const char *buf, const char *mail_type) {
   char *mailer;
   int mailer_has_subj_line;
   lListElem *ep;
   const char *user, *host;

   DENTER(TOP_LAYER, "cull_mail");

   mailer = mconf_get_mailer();
   mailer_has_subj_line = 1;

   if (!buf) {
      buf = subj;
   }

   if (user_list) {
      for_each(ep, user_list) {
         user = lGetString(ep, MR_user);
         host = lGetHost(ep, MR_host);
         if (!user && !host) {
            ERROR((SGE_EVENT, MSG_MAIL_EMPTYUSERHOST));
            FREE(mailer);
            DRETURN_VOID;
         } else if (!host) {
            INFO((SGE_EVENT, MSG_MAIL_MAILUSER_SSSS,
                  mail_type, user, mailer, subj ? subj : MSG_MAIL_NOSUBJ));
         } else {
            INFO((SGE_EVENT, MSG_MAIL_MAILUSERHOST_SSSSS,
                  mail_type, user, host, mailer,
                  subj ? subj : MSG_MAIL_NOSUBJ));
         }
         sge_send_mail(progid, mailer, mailer_has_subj_line, user, host, subj, buf);
      }
   }

   FREE(mailer);
   DRETURN_VOID;
}
