repreorder(node *p, boolean *success)
{


  if (p == NULL)
    return;
  tryrearr(p,success);
  if (!p->tip) {
    repreorder(p->next->back,success);
    repreorder(p->next->next->back,success);
  }
}
