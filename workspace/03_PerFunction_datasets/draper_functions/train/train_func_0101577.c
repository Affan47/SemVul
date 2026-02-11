avc_bridgeco_get_plug_section_type(struct fw_unit *unit,
				       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				       unsigned int id, u8 *type)
{
	u8 *buf;
	int err;


	buf = kzalloc(12, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;


	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x07);
	buf[10] = 0xff & ++id;

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9) | BIT(10));
	if ((err >= 0) && (err < 8))
		err = -EIO;
	else if (buf[0] == 0x08)
		err = -ENOSYS;
	else if (buf[0] == 0x0a)
		err = -EINVAL;
	else if (buf[0] == 0x0b)
		err = -EAGAIN;
	if (err < 0)
		goto end;

	*type = buf[11];
	err = 0;
end:
	kfree(buf);
	return err;
}
