wm8350_hpl_jack_handler(int irq, void *data)
{
	struct wm8350_data *priv = data;
	struct wm8350 *wm8350 = priv->wm8350;

#ifndef CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 HPL");
#endif

	if (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_delayed_work(system_power_efficient_wq,
			   &priv->hpl.work, msecs_to_jiffies(200));

	return IRQ_HANDLED;
}
