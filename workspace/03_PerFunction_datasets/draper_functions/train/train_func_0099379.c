cbf_free_node (cbf_node *node)
{
  unsigned int count;

  void *memblock;

  void *vchild;


  if (!node)

    return CBF_ARGUMENT;


  if (node->type == CBF_CATEGORY) {

    unsigned int column;

    for (column = 0; column < node->children; column++) {

      while(node->child[column]->children) {

        cbf_failnez (cbf_delete_columnrow(node->child [column],node->child[column]->children-1))

      }


    }


  }


  if (node->parent)

    for (count = 0; count < node->parent->children; count++)

      if (node->parent->child [count] == node)
      {
        node->parent->children--;

        if (node->parent->children == 0)
        {
          vchild = (void *)node->parent->child;

          cbf_failnez (cbf_free ((void **) &vchild,
                                       &node->parent->child_size))

          node->parent->child = (cbf_node **)vchild;

        }

        else

          if (node->parent->children > count)

            memmove (node->parent->child + count,
                     node->parent->child + count + 1,
                    (node->parent->children - count) * sizeof (cbf_node *));

        break;
      }


  cbf_failnez (cbf_set_children (node, 0))


  if (node->link) {

    cbf_failnez(cbf_free_node(node->link))

    node->link = NULL;

  }


  cbf_free_string (NULL, node->name);


  if (node->context) {

    cbf_failnez (cbf_delete_contextconnection (&node->context))

  }


  memblock = (void *)node;

  return cbf_free ( &memblock, NULL);
}
