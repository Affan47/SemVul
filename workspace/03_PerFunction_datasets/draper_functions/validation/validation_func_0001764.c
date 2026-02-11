soc_tplg_widget_load(struct soc_tplg *tplg,
	struct snd_soc_dapm_widget *w, struct snd_soc_tplg_dapm_widget *tplg_w)
{
	if (tplg->comp && tplg->ops && tplg->ops->widget_load)
		return tplg->ops->widget_load(tplg->comp, w, tplg_w);

	return 0;
}
