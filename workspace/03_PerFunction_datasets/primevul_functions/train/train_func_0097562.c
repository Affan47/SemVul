static int hugetlb_acct_memory(struct hstate *h, long delta)
{
	int ret = -ENOMEM;

	if (!delta)
		return 0;

	spin_lock_irq(&hugetlb_lock);


	if (delta > 0) {
		if (gather_surplus_pages(h, delta) < 0)
			goto out;

		if (delta > allowed_mems_nr(h)) {
			return_unused_surplus_pages(h, delta);
			goto out;
		}
	}

	ret = 0;
	if (delta < 0)
		return_unused_surplus_pages(h, (unsigned long) -delta);

out:
	spin_unlock_irq(&hugetlb_lock);
	return ret;
}
