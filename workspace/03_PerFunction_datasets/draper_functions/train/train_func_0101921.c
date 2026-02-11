oss_get_volume( void )
{
	int v, cmd, devs;
	int curvol = 0;

	if( fd < 0 ) fd = open( mixer_device, O_RDONLY );
	if( fd != -1 ) {

		ioctl( fd, SOUND_MIXER_READ_DEVMASK, &devs );
		if( devs & mixer_dev_mask ) {
			cmd = MIXER_READ( mixer_channel );
		} else {
			return curvol;
		}

		ioctl( fd, cmd, &v );
		curvol = ( v & 0xFF00 ) >> 8;
	}

	return curvol;
}
