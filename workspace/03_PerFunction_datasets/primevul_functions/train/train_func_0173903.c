int Jsi_ValueStrlen(Jsi_Value* v) {


    Jsi_String *s = jsi_ValueString(v);
    if (s == 0 || s->str == 0)
        return 0;
#if JSI__UTF8
    return (int)Jsi_NumUtfChars(s->str, s->len);
#else
    if (s->len>=0) return s->len;
    return (int)Jsi_NumUtfChars(s->str, s->len);
#endif
}
