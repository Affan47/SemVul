hcache_prune(hcache_type_t type)
{
	hostcache_t *hc;
    int extra;

    g_assert((uint) type < HCACHE_MAX);

	hc = caches[type];

#define HALF_PRUNE(x) G_STMT_START {		\
	if (hash_list_length(hc->hostlist) < \
			hash_list_length(caches[x]->hostlist)) \
		hc = caches[x];			\
} G_STMT_END

    switch (type) {
    case HCACHE_VALID_ANY:
		HALF_PRUNE(HCACHE_FRESH_ANY);
        break;
    case HCACHE_VALID_ULTRA:
		HALF_PRUNE(HCACHE_FRESH_ULTRA);
        break;
    case HCACHE_VALID_ULTRA6:
		HALF_PRUNE(HCACHE_FRESH_ULTRA6);
        break;
    case HCACHE_FRESH_ANY:
		HALF_PRUNE(HCACHE_VALID_ANY);
		break;
    case HCACHE_FRESH_ULTRA:
		HALF_PRUNE(HCACHE_VALID_ULTRA);
		break;
    case HCACHE_FRESH_ULTRA6:
		HALF_PRUNE(HCACHE_VALID_ULTRA6);
		break;
    default:
        break;
    }

#undef HALF_PRUNE

    extra = hcache_slots_left(hc->type);
    if (extra >= 0)
        return;

    start_mass_update(hc);

    hcache_require_caught(hc);
	while (extra++ < 0) {
		gnet_host_t *h;


		if (
			(HCACHE_GUESS == hc->type || HCACHE_GUESS6 == hc->type) &&
			random_value(99) < 70
		) {


			h = hash_list_head(hc->hostlist);
			h = hash_list_next(hc->hostlist, h);
			if (NULL == h)
				h = hash_list_head(hc->hostlist);
		} else {
			h = hash_list_tail(hc->hostlist);
		}

		if (NULL == h) {
			g_carp("BUG: asked to remove hosts, "
                "but hostcache list is empty: %s", hc->name);
			break;
		}
		hcache_remove(hc->class, h);
	}

    stop_mass_update(hc);
}
