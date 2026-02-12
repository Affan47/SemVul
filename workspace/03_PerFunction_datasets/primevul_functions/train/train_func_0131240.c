intrusive_ptr<Expression> ExpressionDateFromString::optimize() {
    _dateString = _dateString->optimize();
    if (_timeZone) {
        _timeZone = _timeZone->optimize();
    }

    if (ExpressionConstant::allNullOrConstant({_dateString, _timeZone})) {

        return ExpressionConstant::create(getExpressionContext(), evaluate(Document{}));
    }
    return this;
}
