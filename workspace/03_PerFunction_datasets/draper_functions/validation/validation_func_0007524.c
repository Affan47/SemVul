fscache_objlist_lookup(loff_t *_pos)
{
	struct fscache_object *pobj, *obj = NULL, *minobj = NULL;
	struct rb_node *p;
	unsigned long pos;

	if (*_pos >= (unsigned long) ERR_PTR(-ENOENT))
		return NULL;
	pos = *_pos;


	if (pos == 0)
		return (struct fscache_object *)(long)++(*_pos);
	if (pos < 3)
		return (struct fscache_object *)pos;

	pobj = (struct fscache_object *)pos;
	p = fscache_object_list.rb_node;
	while (p) {
		obj = rb_entry(p, struct fscache_object, objlist_link);
		if (pobj < obj) {
			if (!minobj || minobj > obj)
				minobj = obj;
			p = p->rb_left;
		} else if (pobj > obj) {
			p = p->rb_right;
		} else {
			minobj = obj;
			break;
		}
		obj = NULL;
	}

	if (!minobj)
		*_pos = (unsigned long) ERR_PTR(-ENOENT);
	else if (minobj != obj)
		*_pos = (unsigned long) minobj;
	return minobj;
}
