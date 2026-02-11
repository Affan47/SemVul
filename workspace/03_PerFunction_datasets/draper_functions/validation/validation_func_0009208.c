Object_GetExists(Crossfire_Object *whoptr, void *closure) {
    if (!object_was_destroyed(whoptr->obj, whoptr->obj->count)) {
        Py_INCREF(Py_True);
        return Py_True;
    } else {
        Py_INCREF(Py_False);
        return Py_False;
    }
}
