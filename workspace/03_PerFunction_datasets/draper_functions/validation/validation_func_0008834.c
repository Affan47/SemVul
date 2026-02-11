ask(int level, const char *prefix, const char *fmt, va_list ap)
{


  static char in_ask_already = 0;
  char buf1[1024];
  if (in_ask_already) {
    fprintf(stderr, "logfunctions::ask() should not reenter!!\n");
    return;
  }
  in_ask_already = 1;
  vsnprintf(buf1, sizeof(buf1), fmt, ap);


  if (SIM->get_init_done()) DEV_vga_refresh();


  SIM->set_display_mode(DISP_MODE_CONFIG);
  int val = SIM->log_msg(prefix, level, buf1);
  switch(val)
  {
    case BX_LOG_ASK_CHOICE_CONTINUE:
      break;
    case BX_LOG_ASK_CHOICE_CONTINUE_ALWAYS:

      setonoff(level, ACT_REPORT);
      break;
    case BX_LOG_ASK_CHOICE_DIE:
    case BX_LOG_NOTIFY_FAILED:
      bx_user_quit = (val==BX_LOG_ASK_CHOICE_DIE)?1:0;
      in_ask_already = 0;
      fatal(prefix, buf1, ap, 1);

      BX_PANIC(("in ask(), fatal() should never return!"));
      break;
    case BX_LOG_ASK_CHOICE_DUMP_CORE:
      fprintf(stderr, "User chose to dump core...\n");
#if BX_HAVE_ABORT
      abort();
#else


      {
        char *crashptr = (char *)0; char c = *crashptr;
      }
      fprintf(stderr, "Sorry, I couldn't find your abort() function.  Exiting.");
      exit(0);
#endif
#if BX_DEBUGGER
    case BX_LOG_ASK_CHOICE_ENTER_DEBUG:


      bx_debug_break();
      break;
#elif BX_GDBSTUB
    case BX_LOG_ASK_CHOICE_ENTER_DEBUG:
      bx_gdbstub_break();
      break;
#endif
    default:


      fprintf(stderr, "WARNING: log_msg returned unexpected value %d\n", val);
  }

  SIM->set_display_mode(DISP_MODE_SIM);
  in_ask_already = 0;
}
