vmaster_hook(void *private_data, int enabled)
{
	struct hda_vmaster_mute_hook *hook = private_data;

	if (hook->mute_mode != HDA_VMUTE_FOLLOW_MASTER)
		enabled = hook->mute_mode;
	hook->hook(hook->codec, enabled);
}
