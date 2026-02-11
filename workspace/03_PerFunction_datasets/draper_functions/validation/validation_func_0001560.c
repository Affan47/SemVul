js_TrimString(JSContext *cx, jsval *vp, JSBool trimLeft, JSBool trimRight)
{
    JSString *str;
    const jschar *chars;
    size_t length, begin, end;

    NORMALIZE_THIS(cx, vp, str);
    str->getCharsAndLength(chars, length);
    begin = 0;
    end = length;

    if (trimLeft) {
        while (begin < length && JS_ISSPACE(chars[begin]))
            ++begin;
    }

    if (trimRight) {
        while (end > begin && JS_ISSPACE(chars[end-1]))
            --end;
    }

    str = js_NewDependentString(cx, str, begin, end - begin);
    if (!str)
        return JS_FALSE;

    *vp = STRING_TO_JSVAL(str);
    return JS_TRUE;
}
