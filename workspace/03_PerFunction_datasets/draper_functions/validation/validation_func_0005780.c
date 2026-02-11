peaked_skill(int skill)
{
    return !P_RESTRICTED(skill)
        && P_SKILL(skill) >= P_MAX_SKILL(skill) && (
                                                    (P_ADVANCE(skill) >=
                                                     (unsigned) practice_needed_to_advance(P_SKILL(skill))));
}
