disable_slot (struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = get_slot(hotplug_slot);

	ctrl_dbg(slot->ctrl, "%s: physical_slot = %s\n",
		 __func__, slot_name(slot));

	return shpchp_sysfs_disable_slot(slot);
}
