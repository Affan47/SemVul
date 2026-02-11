tcl_EnvClose(interp, objc, objv, dbenv, envip)
	Tcl_Interp *interp;
	int objc;
	Tcl_Obj * CONST* objv;
	DB_ENV *dbenv;
	DBTCL_INFO *envip;
{
	static const char *closeoptions[] = {
		"-forcesync",
		NULL
	};
	enum closeoptions {
		FORCESYNC
	};
	int i, result, ret, t_ret;
	u_int32_t flags;

	result = TCL_OK;
	flags = 0;
	Tcl_SetResult(interp, "0", TCL_STATIC);
	if (objc > 3) {
		Tcl_WrongNumArgs(interp, 2, objv, "?-forcesync?");
		return (TCL_ERROR);
	} else if (objc == 3) {


		if (Tcl_GetIndexFromObj(interp, objv[2], closeoptions, "option",
		    TCL_EXACT, &i) != TCL_OK)
			return (IS_HELP(objv[2]));

		switch ((enum closeoptions)i) {
			case FORCESYNC:
				flags |= DB_FORCESYNC;
				break;
		}
	}


	ret = __mutex_free(dbenv->env, &envip->i_mutex);
	_debug_check();
	if ((t_ret = dbenv->close(dbenv, flags)) != 0 && ret == 0)
		ret = t_ret;
	result = _ReturnSetup(interp, ret, DB_RETOK_STD(ret), "env close");
	_EnvInfoDelete(interp, envip);
	envip = NULL;
	return (result);
}
