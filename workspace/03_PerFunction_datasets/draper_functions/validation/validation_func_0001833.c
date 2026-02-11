gen_set_volume( struct wm_drive *d, int left, int right )
{
#ifndef OSS_SUPPORT
	struct	cdrom_volctrl v;
#endif
	int	vol;

#ifdef OSS_SUPPORT

	left = left < 0 ? 0 : left > 100 ? 100 : left;
	right = right < 0 ? : right > 100 ? 100 : right;

	vol = ( 0x007f & left ) | ( 0x7f00 & ( right << 8 ) );
	if( ioctl( mixer, MIXER_WRITE( CD_CHANNEL ), &vol ) == -1 )
	  {
	  	perror( "MIXER_WRITE" );
	  	return ( -1 );
	  }
	return ( 0 );
#else


	left = scale_volume(left, 100);
	right = scale_volume(right, 100);

	v.channel0 = v.channel2 = left < 0 ? 0 : left > 255 ? 255 : left;
	v.channel1 = v.channel3 = right < 0 ? 0 : right > 255 ? 255 : right;

	return (ioctl(d->fd, CDROMVOLCTRL, &v));
# endif
}
