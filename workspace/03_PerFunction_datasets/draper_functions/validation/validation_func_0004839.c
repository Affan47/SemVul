HandleComprehendLanguage(bool apply, bool )
{
    if (apply)
        GetTarget()->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_COMPREHEND_LANG);
    else
        GetTarget()->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_COMPREHEND_LANG);
}
