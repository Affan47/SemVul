get_target (targ) char *targ; {
  int hasht;
  register struct rules *current = (struct rules *) NIL;


  if (!*targ)
    return((struct rules *) NIL);

  if (!test_path (targ)) return NULL;

  hasht = hashval (targ, RULETABSIZE);

  if (ruletab[hasht] != (struct rules *) NIL) {
    current = ruletab[hasht];
    while ((current != (struct rules *) NIL ) &&
	   (strcmp (targ, current->name) != 0)) {

      current = current->nextrule;
    }
  }

  if ((current) && (strcmp(targ, current->name) == 0))
    return current;


  return implicit_target (targ);
}
