QueueName(string Uri,MethodConfig const *&Config)
{
   URI U(Uri);

   Config = GetConfig(U.Access);
   if (Config == 0)
      return string();


   if (Config->SingleInstance == true || QueueMode == QueueAccess)
      return U.Access;

   string AccessSchema = U.Access + ':',
	FullQueueName = AccessSchema + U.Host;
   unsigned int Instances = 0, SchemaLength = AccessSchema.length();

   Queue *I = Queues;
   for (; I != 0; I = I->Next) {

      if (I->Name == FullQueueName)
	 return FullQueueName;

      if (I->Name.compare(0, SchemaLength, AccessSchema) == 0)
	 Instances++;
   }

   if (Debug) {
      clog << "Found " << Instances << " instances of " << U.Access << endl;
   }

   if (Instances >= (unsigned int)_config->FindI("Acquire::QueueHost::Limit",10))
      return U.Access;

   return FullQueueName;
}
