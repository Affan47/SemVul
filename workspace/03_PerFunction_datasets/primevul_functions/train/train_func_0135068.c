_match_result(gboolean has_except,
              gboolean has_not_except,
              gboolean has_match,
              gboolean has_match_except)
{
    if (has_except && !has_not_except) {

        nm_assert(!has_match);
        if (has_match_except) {


            return NM_MATCH_SPEC_NEG_MATCH;
        } else {


            return NM_MATCH_SPEC_MATCH;
        }
    }

    if (has_match_except)
        return NM_MATCH_SPEC_NEG_MATCH;
    if (has_match)
        return NM_MATCH_SPEC_MATCH;
    return NM_MATCH_SPEC_NO_MATCH;
}
