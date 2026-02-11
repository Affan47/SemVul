init_persona (void)
{
  sys_uid = geteuid ();
  sys_gid = getegid ();
  user_uid = getuid ();
  user_gid = getgid ();
  print_persona ();
  user_persona ();


  if (sys_uid != user_uid || sys_gid != sys_uid) {
    var_define ("suid-or-sgid", "true");
    var_define (sys_uid != user_uid ? "suid" : "sgid", "true");
  }
}
