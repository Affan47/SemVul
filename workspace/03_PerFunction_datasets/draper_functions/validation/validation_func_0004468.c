ib_umad_ioctl(struct file *filp, unsigned int cmd,
			  unsigned long arg)
{
	switch (cmd) {
	case IB_USER_MAD_REGISTER_AGENT:
		return ib_umad_reg_agent(filp->private_data, (void __user *) arg, 0);
	case IB_USER_MAD_UNREGISTER_AGENT:
		return ib_umad_unreg_agent(filp->private_data, (__u32 __user *) arg);
	case IB_USER_MAD_ENABLE_PKEY:
		return ib_umad_enable_pkey(filp->private_data);
	case IB_USER_MAD_REGISTER_AGENT2:
		return ib_umad_reg_agent2(filp->private_data, (void __user *) arg);
	default:
		return -ENOIOCTLCMD;
	}
}
