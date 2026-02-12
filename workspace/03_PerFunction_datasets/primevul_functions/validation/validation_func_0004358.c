int updateIpTree(u_int32_t key, u_int8_t version,
		 addr_node **vrootp, const char *proto) {
  addr_node *q;
  addr_node **rootp = vrootp;

  if(rootp == (addr_node **)0)
    return 0;

  while(*rootp != (addr_node *)0) {

    if((version == (*rootp)->version) && (key == (*rootp)->addr)) {

      return ++((*rootp)->count);
    }

    rootp = (key < (*rootp)->addr) ?
      &(*rootp)->left :
      &(*rootp)->right;
  }

  q = (addr_node *) malloc(sizeof(addr_node));
  if(q != (addr_node *)0) {
    *rootp = q;

    q->addr = key;
    q->version = version;
    strncpy(q->proto, proto, sizeof(q->proto));
    q->count = UPDATED_TREE;
    q->left = q->right = (addr_node *)0;

    return q->count;
  }

  return(0);
}
