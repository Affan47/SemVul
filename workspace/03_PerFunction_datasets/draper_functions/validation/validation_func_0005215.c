uspoof_cleanup(void) {
    delete gInclusionSet;
    gInclusionSet = NULL;
    delete gRecommendedSet;
    gRecommendedSet = NULL;
    gNfdNormalizer = NULL;
    return TRUE;
}
