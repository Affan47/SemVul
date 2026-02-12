void InMatchExpression::_doSetCollator(const CollatorInterface* collator) {
    _collator = collator;
    _eltCmp = BSONElementComparator(BSONElementComparator::FieldNamesMode::kIgnore, _collator);

    if (!std::is_sorted(_originalEqualityVector.begin(),
                        _originalEqualityVector.end(),
                        _eltCmp.makeLessThan())) {


        std::sort(
            _originalEqualityVector.begin(), _originalEqualityVector.end(), _eltCmp.makeLessThan());
    }


    _equalitySet = _eltCmp.makeBSONEltFlatSet(_originalEqualityVector);
}
