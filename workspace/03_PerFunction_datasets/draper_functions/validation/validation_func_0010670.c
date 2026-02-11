GetSignature()
{
   if (mSignature == NULL)
   {
      mSignature = new CommandSignature();
      BuildSignature(*mSignature);
   }
   return *mSignature;
}
