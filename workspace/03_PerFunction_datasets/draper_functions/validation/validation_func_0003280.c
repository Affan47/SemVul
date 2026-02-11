OnEffectDummy(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget, ObjectGuid originalCasterGuid)
{
    return m_pOnEffectDummyGO != NULL && m_pOnEffectDummyGO(pCaster, spellId, effIndex, pTarget, originalCasterGuid);
}
