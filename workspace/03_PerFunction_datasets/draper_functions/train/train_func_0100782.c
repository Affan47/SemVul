wm_set_vol(struct snd_ice1712 *ice, unsigned int index,
			unsigned short vol, unsigned short master)
{
	unsigned char nvol;

	if ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE))
		nvol = 0;
	else
		nvol = 127 - wm_vol[(((vol & ~WM_VOL_MUTE) *
			(master & ~WM_VOL_MUTE)) / 127) & WM_VOL_MAX];

	wm_put(ice, index, nvol);
	wm_put_nocache(ice, index, 0x180 | nvol);
}
