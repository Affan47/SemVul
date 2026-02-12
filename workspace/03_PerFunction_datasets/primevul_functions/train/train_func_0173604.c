static int fastVarFree(Jsi_Interp *interp, void *ptr) {
    FastVar *fv = ptr;
    Jsi_Value *v = fv->var.lval;
    if (v) {


    }
    return JSI_OK;
}
