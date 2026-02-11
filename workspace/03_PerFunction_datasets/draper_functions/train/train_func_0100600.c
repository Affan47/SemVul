GetBoomLength(Tube *tube) {

  double  max=0;
  double  min=0;
  bool    first;

  first = true;
  while(tube != NULL) {
    if (first == true) {
      if (tube->e1.x > tube->e2.x)
        max = tube->e1.x;
      else
        max = tube->e2.x;
      if (tube->e1.x < tube->e2.x)
        min = tube->e2.x;
      else
        min = tube->e1.x;
      first = false;
    } else {
      if (tube->e1.x > max)
        max = tube->e1.x;
      if (tube->e2.x > max)
        max = tube->e2.x;
      if (tube->e1.x < min)
        min = tube->e1.x;
      if (tube->e2.x < min)
        min = tube->e2.x;
    }
    tube = tube->next;
  }

  return (max - min);

}
