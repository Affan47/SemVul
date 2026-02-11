sh_tmu_clock_event_set_state(struct clock_event_device *ced,
					int periodic)
{
	struct sh_tmu_channel *ch = ced_to_sh_tmu(ced);


	if (clockevent_state_oneshot(ced) || clockevent_state_periodic(ced))
		sh_tmu_disable(ch);

	dev_info(&ch->tmu->pdev->dev, "ch%u: used for %s clock events\n",
		 ch->index, periodic ? "periodic" : "oneshot");
	sh_tmu_clock_event_start(ch, periodic);
	return 0;
}
