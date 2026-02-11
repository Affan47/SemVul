cb_enable(GtkWidget *button, gpointer data)
    {
	GList	*list;
	CpuMon	*cpu;

	cpu_enabled = GTK_TOGGLE_BUTTON(button)->active;
	for (list = cpu_mon_list; list; list = list->next)
		{
		cpu = (CpuMon *) list->data;
		if (enable_cpu_visibility(cpu) && cpu->enabled)
			gkrellm_reset_and_draw_chart(cpu->chart);
		gkrellm_apply_launcher(&cpu->launch_entry, &cpu->tooltip_entry,
					cpu->chart->panel, &cpu->launch, gkrellm_launch_button_cb);
		gkrellm_reset_alert_soft(cpu->alert);
		}
	if (cpu_enabled)
		gkrellm_spacers_show(mon_cpu);
	else
		gkrellm_spacers_hide(mon_cpu);
	}
