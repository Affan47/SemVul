static PHP_INI_MH(OnChangeMailForceExtra)
{

	if (stage == PHP_INI_STAGE_HTACCESS) {
			return FAILURE;
	}
	return SUCCESS;
}
