write_reg_fp(struct i2c_client *client, u16 addr, u16 val)
{
	struct go7007 *go = i2c_get_adapdata(client->adapter);
	struct go7007_usb *usb;
	int rc;
	u8 *buf;
	struct s2250 *dec = i2c_get_clientdata(client);

	if (go == NULL)
		return -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		return -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);

	if (buf == NULL)
		return -ENOMEM;


	memset(buf, 0xcd, 6);

	usb = go->hpi_context;
	if (mutex_lock_interruptible(&usb->i2c_lock) != 0) {
		dev_info(&client->dev, "i2c lock failed\n");
		kfree(buf);
		return -EINTR;
	}
	rc = go7007_usb_vendor_request(go, 0x57, addr, val, buf, 16, 1);
	mutex_unlock(&usb->i2c_lock);
	if (rc < 0) {
		kfree(buf);
		return rc;
	}

	if (buf[0] == 0) {
		unsigned int subaddr, val_read;

		subaddr = (buf[4] << 8) + buf[5];
		val_read = (buf[2] << 8) + buf[3];
		kfree(buf);
		if (val_read != val) {
			dev_info(&client->dev, "invalid fp write %x %x\n",
				 val_read, val);
			return -EFAULT;
		}
		if (subaddr != addr) {
			dev_info(&client->dev, "invalid fp write addr %x %x\n",
				 subaddr, addr);
			return -EFAULT;
		}
	} else {
		kfree(buf);
		return -EFAULT;
	}


	if (addr == 0x12b)
		dec->reg12b_val = val;

	return 0;
}
