strengthOrder(int32_t order) const
{
    UCollationStrength s = ucol_getStrength(m_data_->iteratordata_.coll);

    if (s == UCOL_PRIMARY) {
        order &= RuleBasedCollator::PRIMARYDIFFERENCEONLY;
    }
    else if (s == UCOL_SECONDARY) {
        order &= RuleBasedCollator::SECONDARYDIFFERENCEONLY;
    }

    return order;
}
