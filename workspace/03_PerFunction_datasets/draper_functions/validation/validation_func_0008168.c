deleteGeneration2(const Path & profile, unsigned int gen)
{
    printMsg(lvlInfo, format("removing generation %1%") % gen);
    deleteGeneration(profile, gen);
}
