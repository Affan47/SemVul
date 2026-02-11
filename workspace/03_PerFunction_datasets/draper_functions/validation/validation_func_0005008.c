slapi_mods_add_modbvps( Slapi_Mods *smods, int modtype, const char *type, struct berval **bvps )
{
	LDAPMod *mod;

	if (NULL == smods) {
		return;
	}
	mod = (LDAPMod *) slapi_ch_malloc(sizeof(LDAPMod));
	mod->mod_type = slapi_ch_strdup( type );
	mod->mod_op = modtype | LDAP_MOD_BVALUES;
	mod->mod_bvalues = NULL;

	if (NULL != bvps)
	{
		int num_values, i;
		num_values = 0;

		while (NULL != bvps[num_values])
		{
			num_values++;
		}
		mod->mod_bvalues = (struct berval **)slapi_ch_malloc((num_values + 1) *
			sizeof(struct berval *));
		for (i = 0; i < num_values; i++)
		{
			mod->mod_bvalues[i] = ber_bvdup((struct berval *)bvps[i]);
		}
		mod->mod_bvalues[num_values] = NULL;
	}
	slapi_mods_add_ldapmod(smods, mod);
}
