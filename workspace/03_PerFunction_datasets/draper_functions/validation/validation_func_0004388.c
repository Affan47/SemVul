paride_unregister(PIP * pr)
{
	if (!pr)
		return;
	if (protocols[pr->index] != pr) {
		printk("paride: %s not registered\n", pr->name);
		return;
	}
	protocols[pr->index] = NULL;
}
