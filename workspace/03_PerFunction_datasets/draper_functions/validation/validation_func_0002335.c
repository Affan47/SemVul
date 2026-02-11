stmemNodeRefCreate(mem_node_ref * r)
{
    assert(r->node == NULL);
    r->node = memAllocate(MEM_MEM_NODE);
    r->node->uses = 0;
    r->node->next = NULL;
    r->node->len = 4096;
    r->offset = 0;
}
