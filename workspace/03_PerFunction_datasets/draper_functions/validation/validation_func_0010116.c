dapm_power_one_widget(struct snd_soc_dapm_widget *w,
				  struct list_head *up_list,
				  struct list_head *down_list)
{
	int power;

	switch (w->id) {
	case snd_soc_dapm_pre:
		dapm_seq_insert(w, down_list, false);
		break;
	case snd_soc_dapm_post:
		dapm_seq_insert(w, up_list, true);
		break;

	default:
		power = dapm_widget_power_check(w);

		dapm_widget_set_power(w, power, up_list, down_list);
		break;
	}
}
