cbf_find_parent (cbf_node **parent, const cbf_node *node,
                     CBF_NODETYPE type)
{


  node = cbf_get_link (node);


  if (!node)

    return CBF_ARGUMENT;


  while (node)
  {
    if (node->type == type)
    {
      if (parent)

        *parent = (cbf_node *) node;

      return 0;
    }

    node = node->parent;
  }


  return CBF_NOTFOUND;
}
