dsp_core_reset(dsp_core_t *dsp_core)
{
	int i;

#if DEBUG
	fprintf(stderr, "Dsp: core reset\n");
#endif


	dsp_core_shutdown(dsp_core);


	memset((void*)dsp_core->periph, 0,sizeof(dsp_core->periph));
	memset(dsp_core->stack, 0,sizeof(dsp_core->stack));
	memset(dsp_core->registers, 0,sizeof(dsp_core->registers));

	dsp_core->bootstrap_pos = 0;


	dsp_core->pc = 0x0000;
	dsp_core->registers[DSP_REG_OMR]=0x02;
	for (i=0;i<8;i++) {
		dsp_core->registers[DSP_REG_M0+i]=0x00ffff;
	}


	dsp_core->interrupt_state = DSP_INTERRUPT_NONE;
	dsp_core->interrupt_instr_fetch = -1;
	dsp_core->interrupt_save_pc = -1;
	dsp_core->swi_inter = 0;


	dsp_core->periph[DSP_SPACE_X][DSP_HOST_HSR]=(1<<DSP_HOST_HSR_HTDE);


	dsp_core->hostport[CPU_HOST_CVR]=0x12;
	dsp_core->hostport[CPU_HOST_ISR]=(1<<CPU_HOST_ISR_TRDY)|(1<<CPU_HOST_ISR_TXDE);
	dsp_core->hostport[CPU_HOST_IVR]=0x0f;


	dsp_core->periph[DSP_SPACE_X][DSP_IPR]=0;
	dsp_core->periph[DSP_SPACE_X][DSP_BCR]=0xffff;


	dsp_core->loop_rep = 0;

#if DEBUG
	fprintf(stderr, "Dsp: reset done\n");
#endif


	if (dsp_core->use_thread) {
		if (dsp_core->semaphore == NULL) {
			dsp_core->semaphore = SDL_CreateSemaphore(0);
		}
		if (dsp_core->mutex == NULL) {
			dsp_core->mutex = SDL_CreateMutex();
		}
		if (dsp_core->thread == NULL) {
			dsp_core->thread = SDL_CreateThread(dsp56k_exec_thread, dsp_core);
		}
	} else {
		dsp56k_init_cpu(dsp_core);
	}
}
