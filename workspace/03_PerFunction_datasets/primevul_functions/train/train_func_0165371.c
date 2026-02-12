static void ResetAdapter(struct s_smc *smc)
{

	PRINTK(KERN_INFO "[fddi: ResetAdapter]\n");


	card_stop(smc);


	mac_drv_clear_tx_queue(smc);
	mac_drv_clear_rx_queue(smc);


	smt_reset_defaults(smc, 1);

	init_smt(smc, (smc->os.dev)->dev_addr);

	smt_online(smc, 1);
	STI_FBI();


	skfp_ctl_set_multicast_list_wo_lock(smc->os.dev);
}
