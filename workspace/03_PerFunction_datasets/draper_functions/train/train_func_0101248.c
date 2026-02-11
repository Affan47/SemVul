calcmove(node *root) {
  expandnode(root);
  if (!root->son) return(0);
  if (debug) printf("calcmove() initial nodes = %d\n",nodes);
  evaluated = 0;
  if (root->son->brother) {
    int x;
    for (x = 1; abs(root->value)<28000 && fullexpand(root,x); x++);
    piece saveboard[45]; memmove(saveboard,b,sizeof(b));
    while (abs(root->value)<28000) {
      x = descend(root);
      memmove(b,saveboard,sizeof(b));
      if (!x) break;
    }
  }
  if (debug) printf(" evaluated %d, nodes = %d\n", evaluated, nodes);
  return(root->son);
}
