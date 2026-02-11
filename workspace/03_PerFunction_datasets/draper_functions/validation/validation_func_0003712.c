G3d_cache_hash_load_name(G3d_cache_hash * h, int name, int index)
{
    if (name >= h->nofNames)
	G3d_fatalError("G3d_cache_hash_load_name: name out of range");

    if (h->active[name] != 0)
	G3d_fatalError("G3d_cache_hash_load_name: name already in hashtable");

    h->index[name] = index;
    h->active[name] = 1;
}
