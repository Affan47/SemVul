jd_access (dn, amode)
     char *dn;
     int amode;
{
  JD_WNN_DEAD return (js_access (jl_env (buf), dn, amode));
}
