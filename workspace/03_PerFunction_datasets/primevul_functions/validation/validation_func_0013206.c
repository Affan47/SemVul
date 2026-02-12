sv_mail (name)
     char *name;
{


  if (name[4] == 'C')
    reset_mail_timer ();
  else
    {
      free_mail_files ();
      remember_mail_dates ();
    }
}
