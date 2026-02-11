count_obj(chain, total_count, total_size, top, recurse)
	struct obj *chain;
	long *total_count;
	long *total_size;
	boolean top;
	boolean recurse;
{
	long count, size;
	struct obj *obj;

	for (count = size = 0, obj = chain; obj; obj = obj->nobj) {
	    if (top) {
		count++;
		size += sizeof(struct obj) + obj->oxlth + obj->onamelth;
	    }
	    if (recurse && obj->cobj)
		count_obj(obj->cobj, total_count, total_size, TRUE, TRUE);
	}
	*total_count += count;
	*total_size += size;
}
