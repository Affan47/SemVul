static int dvb_frontend_ioctl(struct file *file, unsigned int cmd, void *parg)
{
	struct dvb_device *dvbdev = file->private_data;
	struct dvb_frontend *fe = dvbdev->priv;
	struct dvb_frontend_private *fepriv = fe->frontend_priv;
	int err;

	dev_dbg(fe->dvb->device, "%s: (%d)\n", __func__, _IOC_NR(cmd));
	if (down_interruptible(&fepriv->sem))
		return -ERESTARTSYS;

	if (fe->exit != DVB_FE_NO_EXIT) {
		up(&fepriv->sem);
		return -ENODEV;
	}


	if ((file->f_flags & O_ACCMODE) == O_RDONLY
	    && (_IOC_DIR(cmd) != _IOC_READ
		|| cmd == FE_GET_EVENT
		|| cmd == FE_DISEQC_RECV_SLAVE_REPLY)) {
		up(&fepriv->sem);
		return -EPERM;
	}

	err = dvb_frontend_handle_ioctl(file, cmd, parg);

	up(&fepriv->sem);
	return err;
}
