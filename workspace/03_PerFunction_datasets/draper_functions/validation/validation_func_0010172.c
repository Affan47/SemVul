prism54_mac_accept(struct islpci_acl *acl, char *mac)
{
	struct mac_entry *entry;
	int res = 0;

	if (mutex_lock_interruptible(&acl->lock))
		return -ERESTARTSYS;

	if (acl->policy == MAC_POLICY_OPEN) {
		mutex_unlock(&acl->lock);
		return 1;
	}

	list_for_each_entry(entry, &acl->mac_list, _list) {
		if (memcmp(entry->addr, mac, ETH_ALEN) == 0) {
			res = 1;
			break;
		}
	}
	res = (acl->policy == MAC_POLICY_ACCEPT) ? !res : res;
	mutex_unlock(&acl->lock);

	return res;
}
