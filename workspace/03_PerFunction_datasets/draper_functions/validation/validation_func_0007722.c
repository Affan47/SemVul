PCA(char which, const int Rows, const int Columns,
                const char* jobname)
{ const char* error;
  FILE* coordinatefile;
  FILE* pcfile;
  const int n = strlen(jobname) + strlen("_pca_array.coords.txt") + 1;
  char* const filename = malloc(n*sizeof(char));
  if (!filename)
  { printf("ERROR: Failed to allocate memory for file name\n");
    return;
  }
  if (which=='g')
  { sprintf(filename, "%s_pca_gene.coords.txt", jobname);
    coordinatefile = fopen(filename, "wt");
    sprintf(filename, "%s_pca_gene.pc.txt", jobname);
    pcfile = fopen(filename, "wt");
    if(!coordinatefile || !pcfile)
    { printf("Error: Unable to open the output file");
      if (coordinatefile) fclose(coordinatefile);
      if (pcfile) fclose(pcfile);
      free(filename);
      return;
    }
    error = PerformGenePCA(coordinatefile, pcfile);
    fclose(coordinatefile);
    fclose(pcfile);
    if (error)
    { puts(error);
      free(filename);
      return;
    }
  }
  else if (which=='a')
  { sprintf(filename, "%s_pca_array.coords.txt", jobname);
    coordinatefile = fopen(filename, "wt");
    sprintf(filename, "%s_pca_array.pc.txt", jobname);
    pcfile = fopen(filename, "wt");
    if(!coordinatefile || !pcfile)
    { printf("Error: Unable to open the output file");
      if (coordinatefile) fclose(coordinatefile);
      if (pcfile) fclose(pcfile);
      free(filename);
      return;
    }
    error = PerformArrayPCA(coordinatefile, pcfile);
    fclose(coordinatefile);
    fclose(pcfile);
    if (error)
    { puts(error);
      free(filename);
      return;
    }
  }
  free(filename);
}
