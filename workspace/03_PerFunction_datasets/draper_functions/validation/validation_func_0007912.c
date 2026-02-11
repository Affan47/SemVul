tpm2_probe(struct tpm_chip *chip)
{
	struct tpm2_cmd cmd;
	int rc;

	cmd.header.in = tpm2_get_tpm_pt_header;
	cmd.params.get_tpm_pt_in.cap_id = cpu_to_be32(TPM2_CAP_TPM_PROPERTIES);
	cmd.params.get_tpm_pt_in.property_id = cpu_to_be32(0x100);
	cmd.params.get_tpm_pt_in.property_cnt = cpu_to_be32(1);

	rc = tpm_transmit(chip, (const u8 *)&cmd, sizeof(cmd), 0);
	if (rc <  0)
		return rc;
	else if (rc < TPM_HEADER_SIZE)
		return -EFAULT;

	if (be16_to_cpu(cmd.header.out.tag) == TPM2_ST_NO_SESSIONS)
		chip->flags |= TPM_CHIP_FLAG_TPM2;

	return 0;
}
