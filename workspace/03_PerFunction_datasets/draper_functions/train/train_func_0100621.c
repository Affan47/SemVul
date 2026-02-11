snd_config_walk(snd_config_t *src,
			   snd_config_t *root,
			   snd_config_t **dst,
			   snd_config_walk_callback_t callback,
			   snd_config_t *private_data)
{
	int err;
	snd_config_iterator_t i, next;

	switch (snd_config_get_type(src)) {
	case SND_CONFIG_TYPE_COMPOUND:
		err = callback(src, root, dst, SND_CONFIG_WALK_PASS_PRE, private_data);
		if (err <= 0)
			return err;
		snd_config_for_each(i, next, src) {
			snd_config_t *s = snd_config_iterator_entry(i);
			snd_config_t *d = NULL;

			err = snd_config_walk(s, root, (dst && *dst) ? &d : NULL,
					      callback, private_data);
			if (err < 0)
				goto _error;
			if (err && d) {
				err = snd_config_add(*dst, d);
				if (err < 0)
					goto _error;
			}
		}
		err = callback(src, root, dst, SND_CONFIG_WALK_PASS_POST, private_data);
		if (err <= 0) {
		_error:
			if (dst && *dst)
				snd_config_delete(*dst);
		}
		break;
	default:
		err = callback(src, root, dst, SND_CONFIG_WALK_PASS_LEAF, private_data);
		break;
	}
	return err;
}
