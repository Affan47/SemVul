ExecSanityChecks(struct Attributes a,struct Promise *pp)

{
if (a.contain.nooutput && a.contain.preview)
   {
   CfOut(cf_error,"","no_output and preview are mutually exclusive (broken promise)");
   PromiseRef(cf_error,pp);
   return false;
   }

#ifdef MINGW
if(a.contain.umask != CF_UNDEFINED)
  {
  CfOut(cf_verbose, "", "contain.umask is ignored on Windows");
  }

if(a.contain.owner != CF_UNDEFINED)
  {
  CfOut(cf_verbose, "", "contain.exec_owner is ignored on Windows");
  }

if(a.contain.group != CF_UNDEFINED)
  {
  CfOut(cf_verbose, "", "contain.exec_group is ignored on Windows");
  }

if(a.contain.chroot != NULL)
  {
  CfOut(cf_verbose, "", "contain.chroot is ignored on Windows");
  }

#else
if (a.contain.umask == CF_UNDEFINED)
   {
   a.contain.umask = 077;
   }
#endif

return true;
}
