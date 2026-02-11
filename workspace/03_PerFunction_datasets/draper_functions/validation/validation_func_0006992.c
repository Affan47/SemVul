ContextCallback(JSContext *cx, uintN contextOp)
{
    JSShellContextData *data;

    switch (contextOp) {
      case JSCONTEXT_NEW: {
        data = NewContextData();
        if (!data)
            return JS_FALSE;
        JS_SetContextPrivate(cx, data);
        JS_SetErrorReporter(cx, my_ErrorReporter);
        JS_SetVersion(cx, JSVERSION_LATEST);
        SetContextOptions(cx);
        break;
      case JSCONTEXT_DESTROY:
        data = GetContextData(cx);
        JS_SetContextPrivate(cx, NULL);
        free(data);
        break;
      }

      default:
        break;
    }
    return JS_TRUE;
}
