_snd_pcm_asym_open(snd_pcm_t **pcmp, const char *name ATTRIBUTE_UNUSED,
			 snd_config_t *root, snd_config_t *conf,
			 snd_pcm_stream_t stream, int mode)
{
	snd_config_iterator_t i, next;
	int err;
	snd_config_t *slave = NULL, *sconf;
	snd_config_for_each(i, next, conf) {
		snd_config_t *n = snd_config_iterator_entry(i);
		const char *id;
		if (snd_config_get_id(n, &id) < 0)
			continue;
		if (snd_pcm_conf_generic_id(id))
			continue;
		if (strcmp(id, "playback") == 0) {
			if (stream == SND_PCM_STREAM_PLAYBACK)
				slave = n;
			continue;
		}
		if (strcmp(id, "capture") == 0) {
			if (stream == SND_PCM_STREAM_CAPTURE)
				slave = n;
			continue;
		}
		SNDERR("Unknown field %s", id);
		return -EINVAL;
	}
	if (! slave) {
		SNDERR("%s slave is not defined",
		       stream == SND_PCM_STREAM_PLAYBACK ? "playback" : "capture");
		return -EINVAL;
	}
	err = snd_pcm_slave_conf(root, slave, &sconf, 0);
	if (err < 0)
		return err;
	err = snd_pcm_open_named_slave(pcmp, name, root, sconf, stream,
				       mode, conf);
	snd_config_delete(sconf);
	return err;
}
