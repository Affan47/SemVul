PyParser_Delete(parser_state *ps)
{


    PyNode_Free(ps->p_tree);
    PyMem_FREE(ps);
}
