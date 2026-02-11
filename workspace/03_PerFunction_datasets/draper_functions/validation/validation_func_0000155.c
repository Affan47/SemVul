make_peer(uint32_t a, Node *n, bool frozen)
{


    if (frozen)
	return 0;

    Node *down[2];
    if (!(down[0] = new_node()))
	return 0;
    if (!(down[1] = new_node())) {
	free_node(down[0]);
	return 0;
    }


    int swivel = ffs_msb(a ^ n->aggregate);

    int bitvalue = (a >> (32 - swivel)) & 1;

    uint32_t mask = (swivel == 1 ? 0 : (0xFFFFFFFFU << (33 - swivel)));

    down[bitvalue]->aggregate = a;
    down[bitvalue]->count = 0;
    down[bitvalue]->child[0] = down[bitvalue]->child[1] = 0;

    *down[1 - bitvalue] = *n;

    n->aggregate = (down[0]->aggregate & mask);
    if (down[0]->aggregate == n->aggregate) {
	n->count = down[0]->count;
	down[0]->count = 0;
    } else
	n->count = 0;
    n->child[0] = down[0];
    n->child[1] = down[1];

    return (n->aggregate == a ? n : down[bitvalue]);
}
