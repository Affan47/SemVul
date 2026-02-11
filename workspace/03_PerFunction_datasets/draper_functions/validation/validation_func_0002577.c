shadow_parent(struct shadow_spine *s)
{
	BUG_ON(s->count != 2);

	return s->count == 2 ? s->nodes[0] : NULL;
}
