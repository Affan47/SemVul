prevHistory(But *but,
			   KeySym keysym, uint keyModifiers, void *context) {
  CliMain  *main = context;
  int  i;

  assert(MAGIC(main));
  if (main->historyBeingViewed == -main->historyLen) {
    return(BUTOUT_ERR);
  }
  if (main->historyBeingViewed == 0) {
    str_copyChars(&main->history[main->historyBeingFilled],
		  butTextin_get(main->tin));
  }
  --main->historyBeingViewed;
  i = main->historyBeingFilled + main->historyBeingViewed;
  if (i < 0)
    i += MAIN_HISTORYMAXLEN;
  butTextin_set(main->tin, str_chars(&main->history[i]), FALSE);
  return(0);
}
