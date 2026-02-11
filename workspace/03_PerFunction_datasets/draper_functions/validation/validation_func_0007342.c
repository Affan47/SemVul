DoCabinetNameTemplate(char* Template)


{
    DPRINT(MID_TRACE, ("Setting cabinet name template to '%s'\n", Template));

    strcpy(CabinetNameTemplate, Template);
    CabinetNameTemplateSet = true;
}
