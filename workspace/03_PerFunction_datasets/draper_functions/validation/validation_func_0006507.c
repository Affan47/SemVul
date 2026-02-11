HandleDamagePercentTaken(bool apply, bool Real)
{
    m_isPeriodic = apply;

    Unit* target = GetTarget();

    if (!Real)
        return;


    bool loading = (target->GetTypeId() == TYPEID_PLAYER && ((Player*)target)->GetSession()->PlayerLoading());

    if (apply)
    {
        if (loading)
            return;


        if (GetSpellProto()->IsFitToFamily(SPELLFAMILY_PALADIN, UI64LIT(0x0000000000000100)))
        {

            if (target->GetObjectGuid() == GetCasterGuid())
                if (Aura* aur = target->GetAura(63225, EFFECT_INDEX_0))
                    m_modifier.m_amount -= aur->GetModifier()->m_amount;
        }
    }
}
