setmetadevice(metadevice *d)
{
	metadevice *old = m->device;

	if (d)
		m->device = d;

	return old;
}
