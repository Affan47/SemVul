handleScriptingElement(const XMLAttributes& attr)
{
    d_scriptingInitScript =
        attr.getValueAsString(InitScriptAttribute, "");
    d_scriptingTerminateScript =
        attr.getValueAsString(TerminateScriptAttribute, "");
}
