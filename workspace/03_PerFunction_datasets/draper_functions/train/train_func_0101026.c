varpool_node_for_asm (tree asmname)
{
  if (symtab_node node = symtab_node_for_asm (asmname))
    if (varpool_node *vnode = dyn_cast <varpool_node> (node))
      return vnode;
  return NULL;
}
