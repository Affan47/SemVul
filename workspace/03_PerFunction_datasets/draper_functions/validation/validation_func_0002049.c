SetUTCTime(JSContext *cx, JSObject *obj, jsdouble t, jsval *vp = NULL)
{
    JS_ASSERT(OBJ_GET_CLASS(cx, obj) == &js_DateClass);

    obj->fslots[JSSLOT_LOCAL_TIME] = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
    if (!js_NewDoubleInRootedValue(cx, t, &obj->fslots[JSSLOT_UTC_TIME]))
        return false;
    if (vp)
        *vp = obj->fslots[JSSLOT_UTC_TIME];
    return true;
}
