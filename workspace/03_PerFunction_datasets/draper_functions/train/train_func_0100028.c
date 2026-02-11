ensMiscellaneoussetNewIni(
    EnsPMiscellaneoussetadaptor msa,
    ajuint identifier,
    AjPStr code,
    AjPStr name,
    AjPStr description,
    ajuint maxlen)
{
    EnsPMiscellaneousset ms = NULL;

    AJNEW0(ms);

    ms->Use        = 1U;
    ms->Identifier = identifier;
    ms->Adaptor    = msa;

    if (code)
        ms->Code = ajStrNewRef(code);

    if (name)
        ms->Name = ajStrNewRef(name);

    if (description)
        ms->Description = ajStrNewRef(description);

    ms->MaximumLength = maxlen;

    return ms;
}
