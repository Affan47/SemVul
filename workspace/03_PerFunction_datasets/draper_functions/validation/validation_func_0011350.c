TclX_WrongArgs (interp, commandNameObj, string)
    Tcl_Interp  *interp;
    Tcl_Obj     *commandNameObj;
    char        *string;
{
    char    *commandName;
    Tcl_Obj *resultPtr = Tcl_GetObjResult (interp);
    int      commandLength;

    commandName = Tcl_GetStringFromObj (commandNameObj, &commandLength);

    Tcl_AppendStringsToObj (resultPtr,
			    tclXWrongArgs,
			    commandName,
			    (char *)NULL);

    if (*string != '\0') {
	Tcl_AppendStringsToObj (resultPtr, " ", string, (char *)NULL);
    }
    return TCL_ERROR;
}
