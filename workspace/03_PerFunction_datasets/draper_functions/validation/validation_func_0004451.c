getCommandArgs(char *p, char **command,
                            YStringArray &args)
{
    p = YConfig::getArgument(command, p, false);
    if (p == 0) {
        msg(_("Missing command argument"));
        return p;
    }
    args.append(*command);

    while (*p) {
        char *argx;


        while (*p && (*p == ' ' || *p == '\t'))
            p++;

        if (*p == '\n')
            break;


        p = YConfig::getArgument(&argx, p, false);
        if (p == 0) {
            msg(_("Bad argument %d"), args.getCount() + 1);
            return p;
        }

        args.append(argx);
        MSG(("ARG: %s\n", argx));
        delete[] argx;
    }
    args.append(0);

    return p;
}
