gsmi_get_variable(efi_char16_t *name,
				      efi_guid_t *vendor, u32 *attr,
				      unsigned long *data_size,
				      void *data)
{
	struct gsmi_nvram_var_param param = {
		.name_ptr = gsmi_dev.name_buf->address,
		.data_ptr = gsmi_dev.data_buf->address,
		.data_len = (u32)*data_size,
	};
	efi_status_t ret = EFI_SUCCESS;
	unsigned long flags;
	size_t name_len = ucs2_strnlen(name, GSMI_BUF_SIZE / 2);
	int rc;

	if (name_len >= GSMI_BUF_SIZE / 2)
		return EFI_BAD_BUFFER_SIZE;

	spin_lock_irqsave(&gsmi_dev.lock, flags);


	memcpy(&param.guid, vendor, sizeof(param.guid));


	memset(gsmi_dev.name_buf->start, 0, gsmi_dev.name_buf->length);
	memcpy(gsmi_dev.name_buf->start, name, name_len * 2);


	memset(gsmi_dev.data_buf->start, 0, gsmi_dev.data_buf->length);


	memset(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	memcpy(gsmi_dev.param_buf->start, &param, sizeof(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_GET_NVRAM_VAR);
	if (rc < 0) {
		printk(KERN_ERR "gsmi: Get Variable failed\n");
		ret = EFI_LOAD_ERROR;
	} else if (rc == 1) {

		ret = EFI_NOT_FOUND;
	} else {

		memcpy(&param, gsmi_dev.param_buf->start, sizeof(param));


		*data_size = min_t(unsigned long, *data_size,
						gsmi_dev.data_buf->length);
		*data_size = min_t(unsigned long, *data_size, param.data_len);


		memcpy(data, gsmi_dev.data_buf->start, *data_size);


		*attr = EFI_VARIABLE_NON_VOLATILE |
			EFI_VARIABLE_BOOTSERVICE_ACCESS |
			EFI_VARIABLE_RUNTIME_ACCESS;
	}

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	return ret;
}
