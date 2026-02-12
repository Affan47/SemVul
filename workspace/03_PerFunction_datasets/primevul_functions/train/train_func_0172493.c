inline bool Parser::IsNaNOrInfinityLiteral(LPCOLESTR str)
{

    return str &&
           (wcscmp(_u("NaN"), str) == 0 ||
           wcscmp(_u("Infinity"), str) == 0 ||
               (CheckForNegativeInfinity && wcscmp(_u("-Infinity"), str) == 0));
}
