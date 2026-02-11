projectClearAll ()
{
  int loop;

  for ( loop = 0; loop <= max_project; loop++ ) {
    if ( projects[loop] ) {
      projectFree ( projects[loop] );
      projects[loop] = 0;
    }
  }
  num_projects = 0;
  last_number = max_project = -1;
}
