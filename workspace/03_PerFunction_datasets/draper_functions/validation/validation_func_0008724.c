new_nodev(NodeValue *v)
{
    if(!v)
        return 0;

    Node *n = (Node *) malloc(sizeof(Node));
    if(!n)
        return 0;

    n->value = v;
    n->next = 0, n->prev = 0, n->last = 0;
    return n;
}
