static void interpObjErase(InterpObj *fo)
{
    SIGASSERTV(fo,INTERPOBJ);
    if (fo->subinterp) {
        Jsi_Interp *interp = fo->subinterp;
        fo->subinterp = NULL;
        Jsi_InterpDelete(interp);


    }
    fo->subinterp = NULL;
}
