bch_inc_gen(struct cache *ca, struct bucket *b)
{
	uint8_t ret = ++b->gen;

	ca->set->need_gc = max(ca->set->need_gc, bucket_gc_gen(b));
	WARN_ON_ONCE(ca->set->need_gc > BUCKET_GC_GEN_MAX);

	return ret;
}
