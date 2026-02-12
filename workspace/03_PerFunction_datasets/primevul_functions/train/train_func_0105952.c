static inline bool vt_in_use(unsigned int i)
{
	const struct vc_data *vc = vc_cons[i].d;


	WARN_CONSOLE_UNLOCKED();

	return vc && kref_read(&vc->port.kref) > 1;
}
