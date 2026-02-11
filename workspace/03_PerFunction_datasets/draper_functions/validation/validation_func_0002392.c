NsTclRenameObjCmd(ClientData arg, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
{
    if (objc != 3) {
        Tcl_WrongNumArgs(interp, 1, objv, "filename1 filename2");
        return TCL_ERROR;
    }
    if (rename(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0) {
        Tcl_AppendStringsToObj(Tcl_GetObjResult(interp), "rename (\"",
		Tcl_GetString(objv[1]), "\", \"",
		Tcl_GetString(objv[2]),
		"\") failed:  ", Tcl_PosixError(interp), NULL);
        return TCL_ERROR;
    }
    return TCL_OK;
}
