dapm_widget_power_read_file(struct file *file,
					   char __user *user_buf,
					   size_t count, loff_t *ppos)
{
	struct snd_soc_dapm_widget *w = file->private_data;
	struct snd_soc_card *card = w->dapm->card;
	enum snd_soc_dapm_direction dir, rdir;
	char *buf;
	int in, out;
	ssize_t ret;
	struct snd_soc_dapm_path *p = NULL;

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	mutex_lock(&card->dapm_mutex);


	if (w->is_supply) {
		in = 0;
		out = 0;
	} else {
		in = is_connected_input_ep(w, NULL);
		out = is_connected_output_ep(w, NULL);
	}

	ret = snprintf(buf, PAGE_SIZE, "%s: %s%s  in %d out %d",
		       w->name, w->power ? "On" : "Off",
		       w->force ? " (forced)" : "", in, out);

	if (w->reg >= 0)
		ret += snprintf(buf + ret, PAGE_SIZE - ret,
				" - R%d(0x%x) mask 0x%x",
				w->reg, w->reg, w->mask << w->shift);

	ret += snprintf(buf + ret, PAGE_SIZE - ret, "\n");

	if (w->sname)
		ret += snprintf(buf + ret, PAGE_SIZE - ret, " stream %s %s\n",
				w->sname,
				w->active ? "active" : "inactive");

	snd_soc_dapm_for_each_direction(dir) {
		rdir = SND_SOC_DAPM_DIR_REVERSE(dir);
		snd_soc_dapm_widget_for_each_path(w, dir, p) {
			if (p->connected && !p->connected(w, p->node[rdir]))
				continue;

			if (!p->connect)
				continue;

			ret += snprintf(buf + ret, PAGE_SIZE - ret,
					" %s  \"%s\" \"%s\"\n",
					(rdir == SND_SOC_DAPM_DIR_IN) ? "in" : "out",
					p->name ? p->name : "static",
					p->node[rdir]->name);
		}
	}

	mutex_unlock(&card->dapm_mutex);

	ret = simple_read_from_buffer(user_buf, count, ppos, buf, ret);

	kfree(buf);
	return ret;
}
