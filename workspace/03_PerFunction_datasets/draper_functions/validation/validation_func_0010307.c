scif_delete_vma(struct scif_endpt *ep, struct vm_area_struct *vma)
{
	struct list_head *item;
	struct scif_vma_info *info;

	spin_lock(&ep->lock);
	list_for_each(item, &ep->rma_info.vma_list) {
		info = list_entry(item, struct scif_vma_info, list);
		if (info->vma == vma) {
			list_del(&info->list);
			kfree(info);
			break;
		}
	}
	spin_unlock(&ep->lock);
}
