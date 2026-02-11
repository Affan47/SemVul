HEputR8(HE_CMD * cmd)
{
    int i;
    int         verbose = NO;
    char       *image = "img#.@.%";
    char       *pal = "pal#";

    for (i = 1; i < cmd->argc; i++)
        if (cmd->argv[i][0] == '-')
            switch (findOpt(cmd->argv[i] + 1))
              {
                  case HE_HELP:
                      puts("putr8 [-image <img>] [-palette <pal>] [-verbose]");
                      puts("\tPut an r8 group into raw image and palette files");
                      puts("\t-image\t\tImage file name template (default \"img#.@.%\")");
                      puts("\t-palette\tPalette file name template (default \"pal#\")");
                      puts("\t-verbose\tTo give output of steps taken");
                      return HE_OK;
                  case HE_IMAGE:
                      image = cmd->argv[++i];
                      break;
                  case HE_PALETTE:
                      pal = cmd->argv[++i];
                      break;
                  case HE_VERBOSE:
                      verbose = YES;
                      break;
                  case HE_NOTFOUND:
                      unkOpt(cmd->argv[i]);
                      return HE_FAIL;
                  case HE_AMBIG:
                      ambigOpt(cmd->argv[i]);
                      return HE_FAIL;
                  default:
                      irrOpt(cmd->argv[i]);
                      return HE_FAIL;
              }
        else
          {
              unkArg(cmd->argv[i]);
              return HE_FAIL;
          }
    return putR8(image, pal, verbose);
}
