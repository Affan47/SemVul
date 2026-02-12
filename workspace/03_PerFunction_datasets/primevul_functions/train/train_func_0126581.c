auth_heimdal_gssapi_version_report(FILE *f)
{


  fprintf(f, "Library version: Heimdal: Runtime: %s\n"
             " Build Info: %s\n",
          heimdal_version, heimdal_long_version);
}
