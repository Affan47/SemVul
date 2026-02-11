VerifyAbsoluteLink(char *destination,char *source,struct Attributes attr,struct Promise *pp)

{ char absto[CF_BUFSIZE];
  char expand[CF_BUFSIZE];
  char linkto[CF_BUFSIZE];

Debug("VerifyAbsoluteLink(%s,%s)\n",destination,source);

if (*source == '.')
   {
   strcpy(linkto,destination);
   ChopLastNode(linkto);
   AddSlash(linkto);
   strcat(linkto,source);
   }
else
   {
   strcpy(linkto,source);
   }

CompressPath(absto,linkto);

expand[0] = '\0';

if (attr.link.when_no_file == cfa_force)
   {
   if (!ExpandLinks(expand,absto,0))
      {
      CfOut(cf_error,""," !! Failed to make absolute link in\n");
      PromiseRef(cf_error,pp);
      return CF_FAIL;
      }
   else
      {
      Debug2("ExpandLinks returned %s\n",expand);
      }
   }
else
   {
   strcpy(expand,absto);
   }

CompressPath(linkto,expand);

return VerifyLink(destination,linkto,attr,pp);
}
