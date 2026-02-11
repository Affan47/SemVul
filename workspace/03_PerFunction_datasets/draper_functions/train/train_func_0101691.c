NsTclWhileObjCmd(arg, interp, objc, objv)
    ClientData arg;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    NsInterp *itPtr = arg;
    NsServer *servPtr = itPtr->servPtr;
    LoopData data;
    int result, value;

    if (objc != 3) {
	Tcl_WrongNumArgs(interp, 1, objv, "test command");
        return TCL_ERROR;
    }
    EnterLoop(servPtr, &data, objc, objv);
    while (1) {
        result = Tcl_ExprBooleanObj(interp, objv[1], &value);
        if (result != TCL_OK) {
	    goto done;
        }
        if (!value) {
            break;
        }
	result = CheckControl(servPtr, interp, &data);
	if (result == TCL_OK) {
            result = Tcl_EvalObjEx(interp, objv[2], 0);
	}
        if ((result != TCL_OK) && (result != TCL_CONTINUE)) {
            if (result == TCL_ERROR) {
                char msg[32 + TCL_INTEGER_SPACE];

                sprintf(msg, "\n    (\"while\" body line %d)",
                        interp->errorLine);
                Tcl_AddErrorInfo(interp, msg);
            }
            break;
        }
    }
    if (result == TCL_BREAK) {
        result = TCL_OK;
    }
    if (result == TCL_OK) {
        Tcl_ResetResult(interp);
    }
done:
    LeaveLoop(servPtr, &data);
    return result;
}
