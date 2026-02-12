showoneopt (
    vimoption_T *p,
    int opt_flags
)
{
  char_u      *varp;
  int save_silent = silent_mode;

  silent_mode = FALSE;
  info_message = TRUE;

  varp = get_varp_scope(p, opt_flags);


  if ((p->flags & P_BOOL) && ((int *)varp == &curbuf->b_changed
                              ? !curbufIsChanged() : !*(int *)varp)) {
    MSG_PUTS("no");
  } else if ((p->flags & P_BOOL) && *(int *)varp < 0) {
    MSG_PUTS("--");
  } else {
    MSG_PUTS("  ");
  }
  MSG_PUTS(p->fullname);
  if (!(p->flags & P_BOOL)) {
    msg_putchar('=');

    option_value2string(p, opt_flags);
    msg_outtrans(NameBuff);
  }

  silent_mode = save_silent;
  info_message = FALSE;
}
