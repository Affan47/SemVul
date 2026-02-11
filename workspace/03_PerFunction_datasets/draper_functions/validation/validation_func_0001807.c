date_parse(JSContext *cx, uintN argc, jsval *vp)
{
    JSString *str;
    jsdouble result;

    if (argc == 0) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }
    str = js_ValueToString(cx, vp[2]);
    if (!str)
        return JS_FALSE;
    vp[2] = STRING_TO_JSVAL(str);
    if (!date_parseString(str, &result)) {
        *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
        return JS_TRUE;
    }

    result = TIMECLIP(result);
    return js_NewNumberInRootedValue(cx, result, vp);
}
