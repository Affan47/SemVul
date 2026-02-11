find_prop_entry(uint prop)
{
    unsigned int hash;
    vm_tadsobj_prop *entry;


    hash = calc_hash(prop);


    for (entry = hash_arr[hash] ; entry != 0 ; entry = entry->nxt)
    {

        if (entry->prop == prop)
            return entry;
    }


    return 0;
}
