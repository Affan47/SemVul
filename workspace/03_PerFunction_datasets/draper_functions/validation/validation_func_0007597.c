modify_params(int narg, char **arg)
{
  if (narg == 0) error->all(FLERR,"Illegal atom_modify command");

  int iarg = 0;
  while (iarg < narg) {
    if (strcmp(arg[iarg],"map") == 0) {
      if (iarg+2 > narg) error->all(FLERR,"Illegal atom_modify command");
      if (strcmp(arg[iarg+1],"array") == 0) map_style = 1;
      else if (strcmp(arg[iarg+1],"hash") == 0) map_style = 2;
      else error->all(FLERR,"Illegal atom_modify command");
      if (domain->box_exist)
        error->all(FLERR,
                   "Atom_modify map command after simulation box is defined");
      iarg += 2;
    } else if (strcmp(arg[iarg],"first") == 0) {
      if (iarg+2 > narg) error->all(FLERR,"Illegal atom_modify command");
      if (strcmp(arg[iarg+1],"all") == 0) {
        delete [] firstgroupname;
        firstgroupname = NULL;
      } else {
        int n = strlen(arg[iarg+1]) + 1;
        firstgroupname = new char[n];
        strcpy(firstgroupname,arg[iarg+1]);
        sortfreq = 0;
      }
      iarg += 2;
    } else if (strcmp(arg[iarg],"sort") == 0) {
      if (iarg+3 > narg) error->all(FLERR,"Illegal atom_modify command");
      sortfreq = force->inumeric(FLERR,arg[iarg+1]);
      userbinsize = force->numeric(FLERR,arg[iarg+2]);
      if (sortfreq < 0 || userbinsize < 0.0)
        error->all(FLERR,"Illegal atom_modify command");
      if (sortfreq >= 0 && firstgroupname)
        error->all(FLERR,"Atom_modify sort and first options "
                   "cannot be used together");
      iarg += 3;
    } else error->all(FLERR,"Illegal atom_modify command");
  }
}
