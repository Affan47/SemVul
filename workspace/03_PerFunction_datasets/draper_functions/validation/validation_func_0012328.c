addMatchSetTo(UnicodeSet& toUnionTo) const {
    if (maxCount > 0) {
        matcher->toMatcher()->addMatchSetTo(toUnionTo);
    }
}
