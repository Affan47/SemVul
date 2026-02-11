setNextRowCut(const OsiRowCut & cut)
{
    nextRowCut_ = new OsiRowCut(cut);
    nextRowCut_->setEffectiveness(COIN_DBL_MAX);
}
