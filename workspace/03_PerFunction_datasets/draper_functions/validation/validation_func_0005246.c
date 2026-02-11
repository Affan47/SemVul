smi_start_processing(void       *send_info,
				ipmi_smi_t intf)
{
	struct smi_info *new_smi = send_info;
	int             enable = 0;

	new_smi->intf = intf;


	setup_timer(&new_smi->si_timer, smi_timeout, (long)new_smi);
	new_smi->timer_can_start = true;
	smi_mod_timer(new_smi, jiffies + SI_TIMEOUT_JIFFIES);


	if (new_smi->irq_setup)
		new_smi->irq_setup(new_smi);


	if (new_smi->intf_num < num_force_kipmid)
		enable = force_kipmid[new_smi->intf_num];


	else if ((new_smi->si_type != SI_BT) && (!new_smi->irq))
		enable = 1;

	if (enable) {
		new_smi->thread = kthread_run(ipmi_thread, new_smi,
					      "kipmi%d", new_smi->intf_num);
		if (IS_ERR(new_smi->thread)) {
			dev_notice(new_smi->dev, "Could not start"
				   " kernel thread due to error %ld, only using"
				   " timers to drive the interface\n",
				   PTR_ERR(new_smi->thread));
			new_smi->thread = NULL;
		}
	}

	return 0;
}
