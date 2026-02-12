static long snd_pcm_oss_ioctl_compat(struct file *file, unsigned int cmd,
				     unsigned long arg)
{


	return snd_pcm_oss_ioctl(file, cmd, (unsigned long)compat_ptr(arg));
}
