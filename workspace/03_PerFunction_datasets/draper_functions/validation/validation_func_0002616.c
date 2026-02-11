PrintLevelName(FILE *stream, int episode, int level)
{
    PrintBanner(stream);

    switch (discovered_gamemode)
    {

        case doom:
            fprintf(stream, "E%iM%i\n", episode + 1, level + 1);
            break;
        case doom2:
            fprintf(stream, "MAP%02i\n", level + 1);
            break;
        default:
        case indetermined:
            fprintf(stream, "E%iM%i / MAP%02i\n",
                    episode + 1, level + 1, level + 1);
            break;
    }

    PrintBanner(stream);
}
