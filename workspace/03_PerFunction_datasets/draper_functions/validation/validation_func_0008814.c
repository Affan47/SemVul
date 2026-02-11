MoveInLineOfSight(Unit* pWho) override
    {

        if (pWho->GetEntry() == NPC_RAJAXX && m_creature->IsWithinDistInMap(pWho, 50.0f))
        {
            AttackStart(pWho);
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }
