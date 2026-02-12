static inline __u32 inotify_arg_to_mask(u32 arg)
{
	__u32 mask;


	mask = (FS_IN_IGNORED | FS_EVENT_ON_CHILD | FS_UNMOUNT);


	mask |= (arg & (IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK));

	return mask;
}
