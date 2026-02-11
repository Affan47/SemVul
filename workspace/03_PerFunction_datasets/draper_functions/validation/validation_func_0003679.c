wontoption (int option)
{
  if (do_dont_resp[option])
    {
      --do_dont_resp[option];
      if (do_dont_resp[option] && my_state_is_dont (option))
	--do_dont_resp[option];
    }

  if ((do_dont_resp[option] == 0) && my_want_state_is_do (option))
    {

      switch (option)
	{

#ifdef	KLUDGELINEMODE
	case TELOPT_SGA:
	  if (!kludgelinemode)
	    break;

#endif
	case TELOPT_ECHO:
	  settimer (modenegotiated);
	  break;

	case TELOPT_TM:
	  if (flushout)
	    flushout = 0;
	  set_my_want_state_dont (option);
	  set_my_state_dont (option);
	  return;

	default:
	  break;
	}
      set_my_want_state_dont (option);
      if (my_state_is_do (option))
	send_dont (option, 0);
      setconnmode (0);
    }
  else if (option == TELOPT_TM)
    {


      if (flushout)
	flushout = 0;
      set_my_want_state_dont (option);
    }
  set_my_state_dont (option);
}
