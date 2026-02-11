find_biggest_volume (boxptr boxlist, int numboxes)


{
  register boxptr boxp;
  register int i;
  register INT32 maxv = 0;
  boxptr which = NULL;

  for (i = 0, boxp = boxlist; i < numboxes; i++, boxp++) {
    if (boxp->volume > maxv) {
      which = boxp;
      maxv = boxp->volume;
    }
  }
  return which;
}
