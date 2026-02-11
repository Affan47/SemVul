bintomulti(node **root, node **binroot, node **grbg, long *zeros,
                        unsigned char *zeros2)
{

  node *left, *right, *newnode, *temp;

  right = (*root)->next->next->back;
  left = (*root)->next->back;
  if (right->tip) {
    (*root)->next = right->back;
    (*root)->next->next = left->back;
    temp = left;
    left = right;
    right = temp;
    right->back->next = *root;
  }
  gnudisctreenode(grbg, &newnode, right->index, endsite, zeros, zeros2);
  newnode->next = right->next;
  newnode->back = left;
  left->back = newnode;
  right->next = newnode;
  (*root)->next->back = (*root)->next->next->back = NULL;
  *binroot = *root;
  (*binroot)->numdesc = 0;
  *root = right;
  (*root)->numdesc++;
  (*root)->back = NULL;
}
