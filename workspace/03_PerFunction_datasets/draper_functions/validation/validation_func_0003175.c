_rl_read_mbstring (first, mb, mlen)
     int first;
     char *mb;
     int mlen;
{
  int i, c;
  mbstate_t ps;

  c = first;
  memset (mb, 0, mlen);
  for (i = 0; c >= 0 && i < mlen; i++)
    {
      mb[i] = (char)c;
      memset (&ps, 0, sizeof (mbstate_t));
      if (_rl_get_char_len (mb, &ps) == -2)
	{

	  RL_SETSTATE (RL_STATE_MOREINPUT);
	  c = rl_read_key ();
	  RL_UNSETSTATE (RL_STATE_MOREINPUT);
	}
      else
	break;
    }
  return c;
}
