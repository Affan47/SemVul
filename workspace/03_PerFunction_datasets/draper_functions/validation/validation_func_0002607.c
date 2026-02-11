AY8910_sh_start(const struct MachineSound *msound)
{
	int chip;
	const struct AY8910interface *intf = msound->sound_interface;

	num = intf->num;

	for (chip = 0;chip < num;chip++)
	{
		if (AY8910_init(sound_name(msound),chip+ym_num,intf->baseclock,
				intf->mixing_level[chip] & 0xffff,
				Machine->sample_rate,
				intf->portAread[chip],intf->portBread[chip],
				intf->portAwrite[chip],intf->portBwrite[chip]) != 0)
			return 1;
		build_mixer_table(chip+ym_num);
	}
	return 0;
}
