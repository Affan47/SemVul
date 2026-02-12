static int get_warn_pwd_expire_from_config(struct pwb_context *ctx)
{
	int ret;
	ret = get_config_item_int(ctx, "warn_pwd_expire",
				  WINBIND_WARN_PWD_EXPIRE);

	if (ret <= 0) {
		return DEFAULT_DAYS_TO_WARN_BEFORE_PWD_EXPIRES;
	}
	return ret;
}
