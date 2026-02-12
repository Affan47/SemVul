asmlinkage __visible void __init xen_start_kernel(void)
{
	struct physdev_set_iopl set_iopl;
	unsigned long initrd_start = 0;
	int rc;

	if (!xen_start_info)
		return;

	xen_domain_type = XEN_PV_DOMAIN;
	xen_start_flags = xen_start_info->flags;

	xen_setup_features();


	pv_info = xen_info;
	pv_ops.init.patch = paravirt_patch_default;
	pv_ops.cpu = xen_cpu_ops;
	xen_init_irq_ops();


	xen_vcpu_info_reset(0);

	x86_platform.get_nmi_reason = xen_get_nmi_reason;

	x86_init.resources.memory_setup = xen_memory_setup;
	x86_init.irqs.intr_mode_select	= x86_init_noop;
	x86_init.irqs.intr_mode_init	= x86_init_noop;
	x86_init.oem.arch_setup = xen_arch_setup;
	x86_init.oem.banner = xen_banner;
	x86_init.hyper.init_platform = xen_pv_init_platform;
	x86_init.hyper.guest_late_init = xen_pv_guest_late_init;


	xen_setup_machphys_mapping();
	xen_init_mmu_ops();


	__supported_pte_mask &= ~_PAGE_GLOBAL;
	__default_kernel_pte_mask &= ~_PAGE_GLOBAL;


	__userpte_alloc_gfp &= ~__GFP_HIGHMEM;


	xen_build_dynamic_phys_to_machine();


	xen_setup_gdt(0);


	get_cpu_cap(&boot_cpu_data);
	x86_configure_nx();


	get_cpu_address_sizes(&boot_cpu_data);


	per_cpu(xen_vcpu_id, 0) = 0;

	idt_setup_early_handler();

	xen_init_capabilities();

#ifdef CONFIG_X86_LOCAL_APIC


	xen_init_apic();
#endif

	if (xen_feature(XENFEAT_mmu_pt_update_preserve_ad)) {
		pv_ops.mmu.ptep_modify_prot_start =
			xen_ptep_modify_prot_start;
		pv_ops.mmu.ptep_modify_prot_commit =
			xen_ptep_modify_prot_commit;
	}

	machine_ops = xen_machine_ops;


	xen_initial_gdt = &per_cpu(gdt_page, 0);

	xen_smp_init();

#ifdef CONFIG_ACPI_NUMA


	acpi_numa = -1;
#endif
	WARN_ON(xen_cpuhp_setup(xen_cpu_up_prepare_pv, xen_cpu_dead_pv));

	local_irq_disable();
	early_boot_irqs_disabled = true;

	xen_raw_console_write("mapping kernel into physical memory\n");
	xen_setup_kernel_pagetable((pgd_t *)xen_start_info->pt_base,
				   xen_start_info->nr_pages);
	xen_reserve_special_pages();


#ifdef CONFIG_X86_32
	pv_info.kernel_rpl = 1;
	if (xen_feature(XENFEAT_supervisor_mode_kernel))
		pv_info.kernel_rpl = 0;
#else
	pv_info.kernel_rpl = 0;
#endif

	xen_reserve_top();


	set_iopl.iopl = 1;
	rc = HYPERVISOR_physdev_op(PHYSDEVOP_set_iopl, &set_iopl);
	if (rc != 0)
		xen_raw_printk("physdev_op failed %d\n", rc);

#ifdef CONFIG_X86_32

	cpu_detect(&new_cpu_data);
	set_cpu_cap(&new_cpu_data, X86_FEATURE_FPU);
	new_cpu_data.x86_capability[CPUID_1_EDX] = cpuid_edx(1);
#endif

	if (xen_start_info->mod_start) {
	    if (xen_start_info->flags & SIF_MOD_START_PFN)
		initrd_start = PFN_PHYS(xen_start_info->mod_start);
	    else
		initrd_start = __pa(xen_start_info->mod_start);
	}


	boot_params.hdr.type_of_loader = (9 << 4) | 0;
	boot_params.hdr.ramdisk_image = initrd_start;
	boot_params.hdr.ramdisk_size = xen_start_info->mod_len;
	boot_params.hdr.cmd_line_ptr = __pa(xen_start_info->cmd_line);
	boot_params.hdr.hardware_subarch = X86_SUBARCH_XEN;

	if (!xen_initial_domain()) {
		add_preferred_console("xenboot", 0, NULL);
		if (pci_xen)
			x86_init.pci.arch_init = pci_xen_init;
	} else {
		const struct dom0_vga_console_info *info =
			(void *)((char *)xen_start_info +
				 xen_start_info->console.dom0.info_off);
		struct xen_platform_op op = {
			.cmd = XENPF_firmware_info,
			.interface_version = XENPF_INTERFACE_VERSION,
			.u.firmware_info.type = XEN_FW_KBD_SHIFT_FLAGS,
		};

		x86_platform.set_legacy_features =
				xen_dom0_set_legacy_features;
		xen_init_vga(info, xen_start_info->console.dom0.info_size);
		xen_start_info->console.domU.mfn = 0;
		xen_start_info->console.domU.evtchn = 0;

		if (HYPERVISOR_platform_op(&op) == 0)
			boot_params.kbd_status = op.u.firmware_info.u.kbd_shift_flags;


		pci_request_acs();

		xen_acpi_sleep_register();


		x86_init.mpparse.find_smp_config = x86_init_noop;
		x86_init.mpparse.get_smp_config = x86_init_uint_noop;

		xen_boot_params_init_edd();
	}

	if (!boot_params.screen_info.orig_video_isVGA)
		add_preferred_console("tty", 0, NULL);
	add_preferred_console("hvc", 0, NULL);
	if (boot_params.screen_info.orig_video_isVGA)
		add_preferred_console("tty", 0, NULL);

#ifdef CONFIG_PCI

	pci_probe &= ~PCI_PROBE_BIOS;
#endif
	xen_raw_console_write("about to get started...\n");


	xen_setup_runstate_info(0);

	xen_efi_init(&boot_params);


#ifdef CONFIG_X86_32
	i386_start_kernel();
#else
	cr4_init_shadow();
	x86_64_start_reservations((char *)__pa_symbol(&boot_params));
#endif
}
