HuffmanTree_make2DTree(HuffmanTree* tree)
{
  unsigned nodefilled = 0;
  unsigned treepos = 0;
  unsigned n, i;

  uivector_resize(&tree->tree2d, tree->numcodes * 2);


  for(n = 0;  n < tree->numcodes * 2; n++) tree->tree2d.data[n] = 32767;

  for(n = 0; n < tree->numcodes; n++)
  for(i = 0; i < tree->lengths.data[n]; i++)
  {
    unsigned char bit = (unsigned char)((tree->tree1d.data[n] >> (tree->lengths.data[n] - i - 1)) & 1);
    if(treepos > tree->numcodes - 2) return 55;
    if(tree->tree2d.data[2 * treepos + bit] == 32767)
    {
      if(i + 1 == tree->lengths.data[n])
      {
        tree->tree2d.data[2 * treepos + bit] = n;
        treepos = 0;
      }
      else
      {
        nodefilled++;
        tree->tree2d.data[2 * treepos + bit] = nodefilled + tree->numcodes;
        treepos = nodefilled;
      }
    }
    else treepos = tree->tree2d.data[2 * treepos + bit] - tree->numcodes;
  }
  for(n = 0;  n < tree->numcodes * 2; n++) if(tree->tree2d.data[n] == 32767) tree->tree2d.data[n] = 0;

  return 0;
}
