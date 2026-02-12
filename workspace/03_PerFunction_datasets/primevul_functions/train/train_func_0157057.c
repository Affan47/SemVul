void do_machine_check(struct pt_regs *regs, long error_code)
{
	struct mca_config *cfg = &mca_cfg;
	struct mce m, *final;
	int i;
	int worst = 0;
	int severity;


	int order = -1;


	int no_way_out = 0;


	int kill_it = 0;
	DECLARE_BITMAP(toclear, MAX_NR_BANKS);
	DECLARE_BITMAP(valid_banks, MAX_NR_BANKS);
	char *msg = "Unknown";


	int lmce = 1;
	int cpu = smp_processor_id();


	if (cpu_is_offline(cpu) ||
	    (crashing_cpu != -1 && crashing_cpu != cpu)) {
		u64 mcgstatus;

		mcgstatus = mce_rdmsrl(MSR_IA32_MCG_STATUS);
		if (mcgstatus & MCG_STATUS_RIPV) {
			mce_wrmsrl(MSR_IA32_MCG_STATUS, 0);
			return;
		}
	}

	ist_enter(regs);

	this_cpu_inc(mce_exception_count);

	if (!cfg->banks)
		goto out;

	mce_gather_info(&m, regs);
	m.tsc = rdtsc();

	final = this_cpu_ptr(&mces_seen);
	*final = m;

	memset(valid_banks, 0, sizeof(valid_banks));
	no_way_out = mce_no_way_out(&m, &msg, valid_banks, regs);

	barrier();


	if (!(m.mcgstatus & MCG_STATUS_RIPV))
		kill_it = 1;


	if (m.cpuvendor == X86_VENDOR_INTEL)
		lmce = m.mcgstatus & MCG_STATUS_LMCES;


	if (!lmce)
		order = mce_start(&no_way_out);

	for (i = 0; i < cfg->banks; i++) {
		__clear_bit(i, toclear);
		if (!test_bit(i, valid_banks))
			continue;
		if (!mce_banks[i].ctl)
			continue;

		m.misc = 0;
		m.addr = 0;
		m.bank = i;

		m.status = mce_rdmsrl(msr_ops.status(i));
		if ((m.status & MCI_STATUS_VAL) == 0)
			continue;


		if (!(m.status & (cfg->ser ? MCI_STATUS_S : MCI_STATUS_UC)) &&
			!no_way_out)
			continue;


		add_taint(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

		severity = mce_severity(&m, cfg->tolerant, NULL, true);


		if ((severity == MCE_KEEP_SEVERITY ||
		     severity == MCE_UCNA_SEVERITY) && !no_way_out)
			continue;
		__set_bit(i, toclear);
		if (severity == MCE_NO_SEVERITY) {


			continue;
		}

		mce_read_aux(&m, i);


		m.severity = severity;

		mce_log(&m);

		if (severity > worst) {
			*final = m;
			worst = severity;
		}
	}


	m = *final;

	if (!no_way_out)
		mce_clear_state(toclear);


	if (!lmce) {
		if (mce_end(order) < 0)
			no_way_out = worst >= MCE_PANIC_SEVERITY;
	} else {


		 if (worst >= MCE_PANIC_SEVERITY && mca_cfg.tolerant < 3)
			mce_panic("Machine check from unknown source",
				NULL, NULL);
	}


	if (cfg->tolerant == 3)
		kill_it = 0;
	else if (no_way_out)
		mce_panic("Fatal machine check on current CPU", &m, msg);

	if (worst > 0)
		mce_report_event(regs);
	mce_wrmsrl(MSR_IA32_MCG_STATUS, 0);
out:
	sync_core();

	if (worst != MCE_AR_SEVERITY && !kill_it)
		goto out_ist;


	if ((m.cs & 3) == 3) {
		ist_begin_non_atomic(regs);
		local_irq_enable();

		if (kill_it || do_memory_failure(&m))
			force_sig(SIGBUS, current);
		local_irq_disable();
		ist_end_non_atomic();
	} else {
		if (!fixup_exception(regs, X86_TRAP_MC))
			mce_panic("Failed kernel mode recovery", &m, NULL);
	}

out_ist:
	ist_exit(regs);
}
