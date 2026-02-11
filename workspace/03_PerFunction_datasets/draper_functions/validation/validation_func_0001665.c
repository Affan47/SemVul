js_InitFunctionClass(JSContext *cx, JSObject *obj)
{
    JSObject *proto;
    JSFunction *fun;

    proto = JS_InitClass(cx, obj, NULL, &js_FunctionClass, Function, 1,
                         function_props, function_methods, NULL, NULL);
    if (!proto)
        return NULL;
    fun = js_NewFunction(cx, proto, NULL, 0, JSFUN_INTERPRETED, obj, NULL);
    if (!fun)
        return NULL;
    fun->u.i.script = js_NewScript(cx, 1, 1, 0, 0, 0, 0, 0);
    if (!fun->u.i.script)
        return NULL;
    fun->u.i.script->code[0] = JSOP_STOP;
    *fun->u.i.script->notes() = SRC_NULL;
#ifdef CHECK_SCRIPT_OWNER
    fun->u.i.script->owner = NULL;
#endif
    return proto;
}
