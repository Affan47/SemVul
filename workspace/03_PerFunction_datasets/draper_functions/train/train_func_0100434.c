JustReachedHome() override
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_SKERAM, FAIL);
        }

        if (m_bIsImage)
        {
            m_creature->ForcedDespawn();
        }
    }
