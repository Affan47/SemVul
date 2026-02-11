Initialize()
{

    m_owner->StopMoving();


    Clear(false, true);


    if (m_owner->GetTypeId() == TYPEID_UNIT && !m_owner->hasUnitState(UNIT_STAT_CONTROLLED))
    {
        MovementGenerator* movement = FactorySelector::selectMovementGenerator((Creature*)m_owner);
        push(movement == NULL ? &si_idleMovement : movement);
        top()->Initialize(*m_owner);
    }
    else
        { push(&si_idleMovement); }
}
