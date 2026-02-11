UpdatePhysicalInput ()
{
  SDL_Event event;


  while (SDL_PollEvent (&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  CloseGame ();
	  puts ("Quit");
	  break;
	case SDL_FCEU_HOTKEY_EVENT:
	  switch (event.user.code)
	    {
	    case HK_PAUSE:
	      TogglePause ();
	      break;
	    default:
	      FCEU_printf ("Warning: unknown hotkey event %d\n",
			   event.user.code);
	    }
	default:

	  break;
	}
    }

}
