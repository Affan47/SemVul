void hrtimers_resume(void)
{
	WARN_ONCE(!irqs_disabled(),
		  KERN_INFO "hrtimers_resume() called with IRQs enabled!");


	retrigger_next_event(NULL);

	clock_was_set_delayed();
}
