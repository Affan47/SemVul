gk20a_instobj_dtor(struct gk20a_instobj *node)
{
	struct gk20a_instmem *imem = node->imem;
	struct gk20a_instobj *obj;
	unsigned long flags;

	spin_lock_irqsave(&imem->lock, flags);

	if (!node->vaddr)
		goto out;

	list_for_each_entry(obj, &imem->vaddr_lru, vaddr_node) {
		if (obj == node) {
			list_del(&obj->vaddr_node);
			break;
		}
	}
	vunmap(node->vaddr);
	node->vaddr = NULL;
	imem->vaddr_use -= nvkm_memory_size(&node->memory);
	nvkm_debug(&imem->base.subdev, "vaddr used: %x/%x\n",
		   imem->vaddr_use, imem->vaddr_max);

out:
	spin_unlock_irqrestore(&imem->lock, flags);
}
