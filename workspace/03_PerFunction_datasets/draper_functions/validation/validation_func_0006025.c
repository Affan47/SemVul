operator==(const CacheIndex &other) const
    {
        const bool isEqual = memcmp(m_index, other.m_index, s_hashedUrlBytes) == 0;
        if (isEqual) {
            Q_ASSERT(m_hash == other.m_hash);
        }
        return isEqual;
    }
