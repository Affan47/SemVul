travsp(node *p)
{
  long i, num_sibs;
  node *sib_ptr, *sib_back_ptr;


  if (p == curtree.root)
    travinit(p);
  if (p->tip)
    travinit(p->back);
  else {
    sib_ptr = p;
    num_sibs = count_sibs(p);
    for (i=0 ; i < num_sibs; i++) {
      sib_ptr      = sib_ptr->next;
      sib_back_ptr = sib_ptr->back;
      travsp(sib_back_ptr);
    }
  }
}
