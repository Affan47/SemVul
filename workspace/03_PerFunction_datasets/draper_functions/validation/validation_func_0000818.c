JS_LookupPropertyById(JSContext *cx, JSObject *obj, jsid id, jsval *vp)
{
    JSObject *obj2;
    JSProperty *prop;

    CHECK_REQUEST(cx);
    return LookupPropertyById(cx, obj, id, JSRESOLVE_QUALIFIED, &obj2, &prop) &&
           LookupResult(cx, obj, obj2, prop, vp);
}
