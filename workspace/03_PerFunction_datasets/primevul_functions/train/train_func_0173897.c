static void ValueFree(Jsi_Interp *interp, Jsi_Value* v)
{
    SIGASSERTV(v,VALUE);

    switch (v->vt) {
        case JSI_VT_OBJECT:
            Jsi_ObjDecrRefCount(interp, v->d.obj);
            break;
        case JSI_VT_VARIABLE:
            assert(v->d.lval != v);
            Jsi_DecrRefCount(interp, v->d.lval);
            break;
        case JSI_VT_STRING:
            if (v->d.s.str && !v->f.bits.isstrkey) {
                Jsi_Free(v->d.s.str);


            }
            break;
        default:
            break;
    }
    v->vt = JSI_VT_UNDEF;
}
