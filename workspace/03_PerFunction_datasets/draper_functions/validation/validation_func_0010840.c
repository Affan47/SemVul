calcscore()
    {
        if(numuses > 0)
        {
            score = 2.0f * powf(numuses, -0.5f);
            if(rank >= 3) score += powf(1.0f - (rank - 3)/float(MAXVCACHE - 3), 1.5f);
            else if(rank >= 0) score += 0.75f;
        }
        else score = -1.0f;
    }
