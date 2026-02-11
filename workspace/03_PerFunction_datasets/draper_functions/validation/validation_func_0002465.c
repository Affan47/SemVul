vmbus_bus_init(void)
{
	int ret;


	ret = hv_init();
	if (ret != 0) {
		pr_err("Unable to initialize the hypervisor - 0x%x\n", ret);
		return ret;
	}

	ret = bus_register(&hv_bus);
	if (ret)
		goto err_cleanup;

	hv_setup_vmbus_irq(vmbus_isr);

	ret = hv_synic_alloc();
	if (ret)
		goto err_alloc;


	on_each_cpu(hv_synic_init, NULL, 1);
	ret = vmbus_connect();
	if (ret)
		goto err_connect;

	if (vmbus_proto_version > VERSION_WIN7)
		cpu_hotplug_disable();


	if (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE) {
		register_die_notifier(&hyperv_die_block);
		atomic_notifier_chain_register(&panic_notifier_list,
					       &hyperv_panic_block);
	}

	vmbus_request_offers();

	return 0;

err_connect:
	on_each_cpu(hv_synic_cleanup, NULL, 1);
err_alloc:
	hv_synic_free();
	hv_remove_vmbus_irq();

	bus_unregister(&hv_bus);

err_cleanup:
	hv_cleanup(false);

	return ret;
}
