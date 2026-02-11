wm8958_open_circuit_work(struct work_struct *work)
{
	struct wm8994_priv *wm8994 = container_of(work,
						  struct wm8994_priv,
						  open_circuit_work.work);
	struct device *dev = wm8994->wm8994->dev;

	mutex_lock(&wm8994->accdet_lock);

	wm1811_micd_stop(wm8994->hubs.codec);

	dev_dbg(dev, "Reporting open circuit\n");

	wm8994->jack_mic = false;
	wm8994->mic_detecting = true;

	wm8958_micd_set_rate(wm8994->hubs.codec);

	snd_soc_jack_report(wm8994->micdet[0].jack, 0,
			    wm8994->btn_mask |
			    SND_JACK_HEADSET);

	mutex_unlock(&wm8994->accdet_lock);
}
