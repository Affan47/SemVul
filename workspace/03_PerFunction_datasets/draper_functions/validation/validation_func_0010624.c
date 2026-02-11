resultToString(Result r)
{
   switch(r)
   {
      case AccountNumberCheck::OK:
	 return "Ok";
      case AccountNumberCheck::ERROR:
	 return "ERROR: account and bank do not match";
      case AccountNumberCheck::BANK_NOT_KNOWN:
	 return "Bank is unknown";
      default:
      case AccountNumberCheck::UNKNOWN:
	 return "Validation algorithm unknown";
   }
}
