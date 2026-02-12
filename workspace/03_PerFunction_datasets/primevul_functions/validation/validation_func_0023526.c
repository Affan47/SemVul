int jsi_AllObjOp(Jsi_Interp *interp, Jsi_Obj* obj, int op) {
    if (op==2) {
        Jsi_Obj* o = interp->allObjs;
        while (o) {
            if (o==obj) return 1;
            o = o->next;
        }
        return 0;
    }
    if (op==1) {

        assert(interp->allObjs!=obj);
        obj->next = interp->allObjs;
        if (interp->allObjs)
            interp->allObjs->prev = obj;
        interp->allObjs = obj;
        return 0;
    }
    if (op==0) {

        if (!obj || !interp->allObjs) return 0;
        if (obj == interp->allObjs)
            interp->allObjs = obj->next;
        if (obj->next)
            obj->next->prev = obj->prev;
        if (obj->prev)
            obj->prev->next = obj->next;
        return 0;
    }
    if (op == -1) {


        while (0 && interp->allObjs) {
            printf("NEED CLEANUP: %p\n", interp->allObjs);
            Jsi_ObjDecrRefCount(interp, interp->allObjs);
        }
        return 0;
    }
#if JSI__MEMDEBUG
    assert(0);
    abort();
#endif
    return 0;
}
