frontend_init(struct budget_patch* budget)
{
	switch(budget->dev->pci->subsystem_device) {
	case 0x0000:
	case 0x1013:


		budget->dvb_frontend = dvb_attach(ves1x93_attach, &alps_bsrv2_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsrv2_tuner_set_params;
			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_patch_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_patch_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_patch_set_tone;
			break;
		}


		budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsru6_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
			budget->dvb_frontend->tuner_priv = &budget->i2c_adap;

			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_set_tone;
			break;
		}


		budget->dvb_frontend = dvb_attach(tda8083_attach, &grundig_29504_451_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = grundig_29504_451_tuner_set_params;
			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_set_tone;
			break;
		}
		break;
	}

	if (budget->dvb_frontend == NULL) {
		printk("dvb-ttpci: A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget->dev->pci->vendor,
		       budget->dev->pci->device,
		       budget->dev->pci->subsystem_vendor,
		       budget->dev->pci->subsystem_device);
	} else {
		if (dvb_register_frontend(&budget->dvb_adapter, budget->dvb_frontend)) {
			printk("budget-av: Frontend registration failed!\n");
			dvb_frontend_detach(budget->dvb_frontend);
			budget->dvb_frontend = NULL;
		}
	}
}
