pv_get_scriptvar(struct sip_msg *msg,  pv_param_t *param,
		pv_value_t *res)
{
	int ival = 0;
	char *sval = NULL;
	script_var_t *sv=NULL;

	if(msg==NULL || res==NULL)
		return -1;

	if(param==NULL || param->pvn.u.dname==0)
		return pv_get_null(msg, param, res);

	sv= (script_var_t*)param->pvn.u.dname;

	if(sv->v.flags&VAR_VAL_STR)
	{
		res->rs = sv->v.value.s;
		res->flags = PV_VAL_STR;
	} else {
		sval = sint2str(sv->v.value.n, &ival);

		res->rs.s = sval;
		res->rs.len = ival;

		res->ri = sv->v.value.n;
		res->flags = PV_VAL_STR|PV_VAL_INT|PV_TYPE_INT;
	}
	return 0;
}
