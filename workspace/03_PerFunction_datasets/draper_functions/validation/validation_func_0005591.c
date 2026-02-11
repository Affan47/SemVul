cbf_make_new_child (cbf_node **child, cbf_node *node,
                        CBF_NODETYPE type, const char *name)
{
  cbf_node *newchild;

  int errorcode;


  if (type == CBF_LINK)

    return CBF_ARGUMENT;


  node = cbf_get_link (node);


  cbf_failnez (cbf_make_new_node (&newchild, type, node->context, name))

  errorcode = cbf_add_new_child (node, newchild);

  if (errorcode)
  {
    newchild->name = NULL;

    cbf_free_node (newchild);

    return errorcode;
  }


  if (child)

    *child = newchild;

  return 0;
}
