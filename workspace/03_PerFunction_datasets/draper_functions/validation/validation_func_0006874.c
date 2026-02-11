PushObject(JSContext *cx, JSONParser *jp, JSObject *obj)
{
    jsuint len;
    if (!js_GetLengthProperty(cx, jp->objectStack, &len))
        return JS_FALSE;
    if (len >= JSON_MAX_DEPTH) {
        JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL, JSMSG_JSON_BAD_PARSE);
        return JS_FALSE;
    }

    jsval v = OBJECT_TO_JSVAL(obj);
    JSAutoTempValueRooter tvr(cx, v);


    if (len == 0) {
        *jp->rootVal = v;

        if (!jp->objectStack->defineProperty(cx, INT_TO_JSID(0), *jp->rootVal,
                                             NULL, NULL, JSPROP_ENUMERATE)) {
            return JS_FALSE;
        }
        return JS_TRUE;
    }

    jsval p;
    if (!jp->objectStack->getProperty(cx, INT_TO_JSID(len - 1), &p))
        return JS_FALSE;

    JS_ASSERT(JSVAL_IS_OBJECT(p));
    JSObject *parent = JSVAL_TO_OBJECT(p);
    if (!PushValue(cx, jp, parent, v))
        return JS_FALSE;


    if (!jp->objectStack->defineProperty(cx, INT_TO_JSID(len), v,
                                         NULL, NULL, JSPROP_ENUMERATE)) {
        return JS_FALSE;
    }

    return JS_TRUE;
}
