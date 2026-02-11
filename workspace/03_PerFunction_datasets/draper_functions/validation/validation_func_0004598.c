get_superclass(VMG_ vm_obj_id_t, int sc_idx) const
{
    vm_meta_entry_t *entry;


    entry = get_meta_entry(vmg0_);


    if (entry != 0)
        return entry->meta_->get_supermeta(vmg_ sc_idx);
    else
        return VM_INVALID_OBJ;
}
