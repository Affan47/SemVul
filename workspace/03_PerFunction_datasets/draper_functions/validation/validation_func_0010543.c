set_value(private_settings_t *this, section_t *section,
					  char *key, va_list args, char *value)
{
	char buf[128], keybuf[512];
	kv_t *kv;

	if (snprintf(keybuf, sizeof(keybuf), "%s", key) >= sizeof(keybuf))
	{
		return;
	}
	this->lock->write_lock(this->lock);
	kv = find_value_buffered(section, keybuf, keybuf, args, buf, sizeof(buf),
							 TRUE);
	if (kv)
	{
		settings_kv_set(kv, strdupnull(value), this->contents);
	}
	this->lock->unlock(this->lock);
}
