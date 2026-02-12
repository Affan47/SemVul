bind_args (argv, arg_start, arg_end, start_index)
     char **argv;
     int arg_start, arg_end, start_index;
{
  register int i;
  WORD_LIST *args, *tl;

  for (i = arg_start, args = tl = (WORD_LIST *)NULL; i < arg_end; i++)
    {
      if (args == 0)
	args = tl = make_word_list (make_word (argv[i]), args);
      else
	{
	  tl->next = make_word_list (make_word (argv[i]), (WORD_LIST *)NULL);
	  tl = tl->next;
	}
    }

  if (args)
    {
      if (start_index == 0)
	{


	  shell_name = savestring (args->word->word);
	  FREE (dollar_vars[0]);
	  dollar_vars[0] = savestring (args->word->word);
	  remember_args (args->next, 1);
	  if (debugging_mode)
	    {
	      push_args (args->next);
	      bash_argv_initialized = 1;
	    }
	}
      else
        {
	  remember_args (args, 1);


	  if (debugging_mode)
	    {
	      push_args (args);
	      bash_argv_initialized = 1;
	    }
        }

      dispose_words (args);
    }

  return (i);
}
