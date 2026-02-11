do_interest(Lake *lake, LList *call, char *action)
{
  int i;
  LList *filter, *cargs;
  char *command;
  LInterest *new;

  if (!call || !call->car) {
    fprintf(stderr,"%s: COMMAND required.\n", action);
    return Lnil;
  }
  if (call->car->type != LSTRING) {
    fprintf(stderr, "%s: COMMAND must be a string (got %s)\n",
	    action, LSummarize(call->car));
    return Lnil;
  }
  command = LSTRINGVAL(call->car);


  cargs = call->cdr;

  if ( (i=funcindex(command)) < 0 ) {
    fprintf(stderr, "%s: no such command \"%s\"\n", action,command);
    return Lnil;
  }

  filter = FilterList(cargs);

  if (strcmp(action, "interest")==0) {
    new = NewInterest();
    new->lake = lake;
    new->filter = filter;
    AppendInterest(&(functable[i].interested),  new);
  } else {
    RemoveInterests(&(functable[i].interested), lake, 1, filter);
    LListFree(filter);
  }
  return Lt;
}
