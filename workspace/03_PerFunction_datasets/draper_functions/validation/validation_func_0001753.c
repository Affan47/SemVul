print_prop_tree(FILE *fp,
		     struct fpa_tree *n,
		     int level)
{
  int i;

  if (n != NULL) {

    for (i=0; i<level; i++)
      fprintf(fp, "  ");
    if (n->type == AND)
      fprintf(fp, "and\n");
    else if (n->type == OR)
      fprintf(fp, "or\n");
    else
      print_path(fp, n->path);
    print_prop_tree(fp, n->left, level+1);
    print_prop_tree(fp, n->right, level+1);
  }
}
