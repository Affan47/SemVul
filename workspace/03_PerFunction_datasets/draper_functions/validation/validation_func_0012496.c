VerifyDatabasePromises(struct Promise *pp)

{ struct Attributes a = {{0}};

if (pp->done)
   {
   return;
   }

PromiseBanner(pp);

a = GetDatabaseAttributes(pp);

if (!CheckDatabaseSanity(a,pp))
   {
   return;
   }

if (strcmp(a.database.type,"sql") == 0)
   {
   VerifySQLPromise(a,pp);
   return;
   }

if (strcmp(a.database.type,"ms_registry") == 0)
   {
   VerifyRegistryPromise(a,pp);
   return;
   }
}
