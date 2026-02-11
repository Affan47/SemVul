nvme_nvm_identity(struct nvm_dev *nvmdev, struct nvm_id *nvm_id)
{
	struct nvme_ns *ns = nvmdev->q->queuedata;
	struct nvme_nvm_id *nvme_nvm_id;
	struct nvme_nvm_command c = {};
	int ret;

	c.identity.opcode = nvme_nvm_admin_identity;
	c.identity.nsid = cpu_to_le32(ns->ns_id);
	c.identity.chnl_off = 0;

	nvme_nvm_id = kmalloc(sizeof(struct nvme_nvm_id), GFP_KERNEL);
	if (!nvme_nvm_id)
		return -ENOMEM;

	ret = nvme_submit_sync_cmd(ns->ctrl->admin_q, (struct nvme_command *)&c,
				nvme_nvm_id, sizeof(struct nvme_nvm_id));
	if (ret) {
		ret = -EIO;
		goto out;
	}

	nvm_id->ver_id = nvme_nvm_id->ver_id;
	nvm_id->vmnt = nvme_nvm_id->vmnt;
	nvm_id->cgrps = nvme_nvm_id->cgrps;
	nvm_id->cap = le32_to_cpu(nvme_nvm_id->cap);
	nvm_id->dom = le32_to_cpu(nvme_nvm_id->dom);
	memcpy(&nvm_id->ppaf, &nvme_nvm_id->ppaf,
					sizeof(struct nvme_nvm_addr_format));

	ret = init_grps(nvm_id, nvme_nvm_id);
out:
	kfree(nvme_nvm_id);
	return ret;
}
