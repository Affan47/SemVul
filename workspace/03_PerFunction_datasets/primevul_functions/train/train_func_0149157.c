static void domain_exit(struct dmar_domain *domain)
{
	struct page *freelist;


	rcu_read_lock();
	domain_remove_dev_info(domain);
	rcu_read_unlock();


	put_iova_domain(&domain->iovad);

	freelist = domain_unmap(domain, 0, DOMAIN_MAX_PFN(domain->gaw));

	dma_free_pagelist(freelist);

	free_domain_mem(domain);
}
