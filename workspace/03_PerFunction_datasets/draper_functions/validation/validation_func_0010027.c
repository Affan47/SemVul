R2Splits(const R2Line& line, const R2Span& span)
{


    RNScalar d1 = R2SignedDistance(line, span.Start());
    RNScalar d2 = R2SignedDistance(line, span.End());
    if (RNIsNegative(d1)) {
        if (RNIsPositive(d2)) return 3;
	else return 1;
    }
    else if (RNIsPositive(d1)) {
        if (RNIsNegative(d2)) return 3;
	else return 2;
    }
    else {
        if (RNIsNegative(d2)) return 1;
        else if (RNIsPositive(d2)) return 2;
	else return 0;
    }
}
