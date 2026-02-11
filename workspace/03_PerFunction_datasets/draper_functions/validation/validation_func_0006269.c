uc_mgr_free_device(struct list_head *base)
{
	struct list_head *pos, *npos;
	struct use_case_device *dev;

	list_for_each_safe(pos, npos, base) {
		dev = list_entry(pos, struct use_case_device, list);
		free(dev->name);
		free(dev->comment);
		uc_mgr_free_sequence(&dev->enable_list);
		uc_mgr_free_sequence(&dev->disable_list);
		uc_mgr_free_transition(&dev->transition_list);
		uc_mgr_free_value(&dev->value_list);
		list_del(&dev->list);
		free(dev);
	}
}
