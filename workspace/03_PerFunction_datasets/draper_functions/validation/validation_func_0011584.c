addnode(btree_node* tree, btree_node* newnode, btree_node** oldnode)
{
  btree_node* tmp, * last = NULL;

  if (*oldnode) {
    *oldnode = NULL;
  }

  if (!tree) {
    return (newnode);
  }

  tmp = tree;

  while (tmp) {
    last = tmp;
    if (newnode->data < tmp->data) {
      tmp = tmp->right;
    } else if (newnode->data > tmp->data) {
      tmp = tmp->left;
    } else {
      if (oldnode) {
        *oldnode = tmp;
      }
      return (NULL);
    }
  }

  if (newnode->data < last->data) {
    last->right = newnode;
  } else {
    last->left = newnode;
  }

  return (tree);
}
