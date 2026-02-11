audit_remove_watch_rule(struct audit_krule *krule)
{
	struct audit_watch *watch = krule->watch;
	struct audit_parent *parent = watch->parent;

	list_del(&krule->rlist);

	if (list_empty(&watch->rules)) {


		audit_get_parent(parent);
		audit_remove_watch(watch);
		if (list_empty(&parent->watches))
			fsnotify_destroy_mark(&parent->mark, audit_watch_group);
		audit_put_parent(parent);
	}
}
