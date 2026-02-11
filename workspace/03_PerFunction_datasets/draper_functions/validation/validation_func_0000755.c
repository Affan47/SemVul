snic_free_all_untagged_reqs(struct snic *snic)
{
	struct snic_req_info *rqi;
	struct list_head *cur, *nxt;
	unsigned long flags;

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	list_for_each_safe(cur, nxt, &snic->spl_cmd_list) {
		rqi = list_entry(cur, struct snic_req_info, list);
		list_del_init(&rqi->list);
		if (rqi->sge_va) {
			snic_pci_unmap_rsp_buf(snic, rqi);
			kfree((void *)rqi->sge_va);
			rqi->sge_va = 0;
		}

		snic_req_free(snic, rqi);
	}
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
}
