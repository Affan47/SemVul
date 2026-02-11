GetHappinessState()
{
    if (GetPower(POWER_HAPPINESS) < HAPPINESS_LEVEL_SIZE)
        { return UNHAPPY; }
    else if (GetPower(POWER_HAPPINESS) >= HAPPINESS_LEVEL_SIZE * 2)
        { return HAPPY; }
    else
        { return CONTENT; }
}
