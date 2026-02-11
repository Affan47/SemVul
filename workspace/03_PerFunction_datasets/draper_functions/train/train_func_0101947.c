EffectHealMaxHealth(SpellEffectIndex )
{
    if (!unitTarget)
        { return; }
    if (!unitTarget->IsAlive())
        { return; }

    uint32 heal = m_caster->GetMaxHealth();

    m_healing += heal;
}
