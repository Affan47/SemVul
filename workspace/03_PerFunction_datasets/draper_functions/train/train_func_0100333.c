__zswap_cpu_comp_notifier(struct zswap_pool *pool,
				     unsigned long action, unsigned long cpu)
{
	struct crypto_comp *tfm;

	switch (action) {
	case CPU_UP_PREPARE:
		if (WARN_ON(*per_cpu_ptr(pool->tfm, cpu)))
			break;
		tfm = crypto_alloc_comp(pool->tfm_name, 0, 0);
		if (IS_ERR_OR_NULL(tfm)) {
			pr_err("could not alloc crypto comp %s : %ld\n",
			       pool->tfm_name, PTR_ERR(tfm));
			return NOTIFY_BAD;
		}
		*per_cpu_ptr(pool->tfm, cpu) = tfm;
		break;
	case CPU_DEAD:
	case CPU_UP_CANCELED:
		tfm = *per_cpu_ptr(pool->tfm, cpu);
		if (!IS_ERR_OR_NULL(tfm))
			crypto_free_comp(tfm);
		*per_cpu_ptr(pool->tfm, cpu) = NULL;
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}
