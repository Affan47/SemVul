rl_domove_motion_callback (m)
     _rl_vimotion_cxt *m;
{
  int c, save, r;
  int old_end;

  _rl_vi_last_motion = c = m->motion;


  old_end = rl_end;
  rl_line_buffer[rl_end++] = ' ';
  rl_line_buffer[rl_end] = '\0';

  _rl_dispatch (c, _rl_keymap);


  rl_end = old_end;
  rl_line_buffer[rl_end] = '\0';
  if (rl_point > rl_end)
    rl_point = rl_end;


  if (rl_mark == rl_point)
    return (-1);


  if ((_rl_to_upper (c) == 'W') && rl_point < rl_end && rl_point > rl_mark &&
      !whitespace (rl_line_buffer[rl_point]))
    rl_point--;


  if (m->key == 'c' && rl_point >= rl_mark && (_rl_to_upper (c) == 'W'))
    {

      while (rl_point > rl_mark && whitespace (rl_line_buffer[rl_point]))
	rl_point--;


      if (rl_point == rl_mark)
	rl_point++;
      else
	{


	  if (rl_point >= 0 && rl_point < (rl_end - 1) && !whitespace (rl_line_buffer[rl_point]))
	    rl_point++;
	}
    }

  if (rl_mark < rl_point)
    SWAP (rl_point, rl_mark);

#if defined (READLINE_CALLBACKS)
  if (RL_ISSTATE (RL_STATE_CALLBACK))
    (*rl_redisplay_function)();
#endif

  r = vidomove_dispatch (m);

  return (r);
}
