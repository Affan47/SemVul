recursebook(dxml_element * b)
{
  dxml_element * tmp;
  for (tmp = dxml_get_element_byname(b, "chapter"); tmp; tmp=tmp->next)
    {
      printf ("\n\\chapter{");
      convert_print(dxml_get_PCDATA_bysimplepath(tmp->child, "title"),0);
      printf("}\n\n");
      maybe_label(tmp);
      get_bookchapter (tmp->child,1);
    }
  return 0;
}
