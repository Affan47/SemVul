JS_HasUCProperty(JSContext *cx, JSObject *obj,
                 const jschar *name, size_t namelen,
                 JSBool *vp)
{
    JSBool ok;
    JSObject *obj2;
    JSProperty *prop;

    CHECK_REQUEST(cx);
    ok = LookupUCProperty(cx, obj, name, namelen,
                          JSRESOLVE_QUALIFIED | JSRESOLVE_DETECTING,
                          &obj2, &prop);
    if (ok) {
        *vp = (prop != NULL);
        if (prop)
            obj2->dropProperty(cx, prop);
    }
    return ok;
}
