R2Splits(const R2Line& line, const R2Span& span, R2Span *below_result, R2Span *above_result)
{


    RNScalar d1 = R2SignedDistance(line, span.Start());
    RNScalar d2 = R2SignedDistance(line, span.End());
    if (RNIsNegative(d1)) {
        if (RNIsPositive(d2)) {

	    if (below_result || above_result) {

		R2Point point = span.Point(-d1);
		if (below_result) *below_result = R2Span(span.Start(), point);
		if (above_result) *above_result = R2Span(point, span.End());
	    }
	    return 3;
	}
	else {

	    if (below_result) *below_result = span;
	    return 1;
	}
    }
    else if (RNIsPositive(d1)) {
        if (RNIsNegative(d2)) {

	    if (below_result || above_result) {

		R2Point point = span.Point(d1);
		if (below_result) *below_result = R2Span(span.End(), point);
		if (above_result) *above_result = R2Span(point, span.Start());
	    }
	    return 3;
	}
	else {

	    if (above_result) *above_result = span;
	    return 2;
	}
    }
    else {
        if (RNIsNegative(d2)) {

	    if (below_result) *below_result = span;
	    return 1;
	}
        else if (RNIsPositive(d2)) {

	    if (above_result) *above_result = span;
	    return 2;
	}
	else {

	    if (below_result) *below_result = span;
	    if (above_result) *above_result = span;
	    return 0;
	}
    }
}
