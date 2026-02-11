rddfa_line(char *line, DFA_INFO *dinfo, int *state_max, int *arc_num, int *terminal_max)
{
  DFA_ARC *newarc;
  int state, terminal, next_state;
  unsigned int status;
  char *p;

  if (strmatch(buf, "DFAEND")) return(FALSE);

  if ((p = strtok(line, DELM)) == NULL) {
    jlog("Error: rddfa: failed to parse, corrupted or invalid data?\n");
    return FALSE;
  }
  state = atoi(p);
  if ((p = strtok(NULL, DELM)) == NULL) {
    jlog("Error: rddfa: failed to parse, corrupted or invalid data?\n");
    return FALSE;
  }
  terminal = atoi(p);
  if ((p = strtok(NULL, DELM)) == NULL) {
    jlog("Error: rddfa: failed to parse, corrupted or invalid data?\n");
    return FALSE;
  }
  next_state = atoi(p);
  if ((p = strtok(NULL, DELM)) == NULL) {
    jlog("Error: rddfa: failed to parse, corrupted or invalid data?\n");
    return FALSE;
  }
  sscanf(p, "%x", &status);

  if (state >= dinfo->maxstatenum) {
    dfa_state_expand(dinfo, state+1);
  }
  if (next_state >= dinfo->maxstatenum) {
    dfa_state_expand(dinfo, next_state+1);
  }


  if (status & ACCEPT_S) {
    dinfo->st[state].status |= ACCEPT_S;
  }

  if (state == 0) {
    dinfo->st[state].status |= INITIAL_S;
  }


  if (terminal > 0 || next_state > 0) {

    newarc = (DFA_ARC *)mymalloc(sizeof(DFA_ARC));
    newarc->label    = terminal;
    newarc->to_state = next_state;
    newarc->next     = dinfo->st[state].arc;
    dinfo->st[state].arc = newarc;
    (*arc_num)++;
  }

  if (*state_max < state) *state_max = state;
  if (*terminal_max < terminal) *terminal_max = terminal;

  return(TRUE);
}
