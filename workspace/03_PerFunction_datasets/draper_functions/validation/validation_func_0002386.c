reset_curve(struct shinkos2145_ctx *ctx, int target)
{
	struct s2145_reset_cmd cmd;
	struct s2145_status_hdr *resp = (struct s2145_status_hdr *) rdbuf;
	int ret, num = 0;

	cmd.target = target;

	cmd.hdr.cmd = cpu_to_le16(S2145_CMD_RESET);
	cmd.hdr.len = cpu_to_le16(1);

	if ((ret = s2145_do_cmd(ctx,
				(uint8_t*)&cmd, sizeof(cmd),
				sizeof(*resp),
				&num)) < 0) {
		ERROR("Failed to execute %s command\n", cmd_names(cmd.hdr.cmd));
		return ret;
	}

	return 0;
}
