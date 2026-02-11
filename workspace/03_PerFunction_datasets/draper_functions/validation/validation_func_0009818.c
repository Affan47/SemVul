ubifs_add_orphan(struct ubifs_info *c, ino_t inum)
{
	struct ubifs_orphan *orphan, *o;
	struct rb_node **p, *parent = NULL;

	orphan = kzalloc(sizeof(struct ubifs_orphan), GFP_NOFS);
	if (!orphan)
		return -ENOMEM;
	orphan->inum = inum;
	orphan->new = 1;

	spin_lock(&c->orphan_lock);
	if (c->tot_orphans >= c->max_orphans) {
		spin_unlock(&c->orphan_lock);
		kfree(orphan);
		return -ENFILE;
	}
	p = &c->orph_tree.rb_node;
	while (*p) {
		parent = *p;
		o = rb_entry(parent, struct ubifs_orphan, rb);
		if (inum < o->inum)
			p = &(*p)->rb_left;
		else if (inum > o->inum)
			p = &(*p)->rb_right;
		else {
			ubifs_err(c, "orphaned twice");
			spin_unlock(&c->orphan_lock);
			kfree(orphan);
			return 0;
		}
	}
	c->tot_orphans += 1;
	c->new_orphans += 1;
	rb_link_node(&orphan->rb, parent, p);
	rb_insert_color(&orphan->rb, &c->orph_tree);
	list_add_tail(&orphan->list, &c->orph_list);
	list_add_tail(&orphan->new_list, &c->orph_new);
	spin_unlock(&c->orphan_lock);
	dbg_gen("ino %lu", (unsigned long)inum);
	return 0;
}
