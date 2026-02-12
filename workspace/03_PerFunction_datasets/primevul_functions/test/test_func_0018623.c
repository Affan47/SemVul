void address_space_destroy(AddressSpace *as)
{
    MemoryRegion *root = as->root;


    memory_region_transaction_begin();
    as->root = NULL;
    memory_region_transaction_commit(root);
    QTAILQ_REMOVE(&as->uc->address_spaces, as, address_spaces_link);


    as->root = root;
    flatview_unref(as->current_map);
}
