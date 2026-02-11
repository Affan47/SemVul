registerWorkClassFactory( WorkClassFactory* wcf, bool ASCmode )
{
   if ( ASCmode )  {
      if ( !workClassFactoriesASC )
         workClassFactoriesASC = new WorkerClassList;

      workClassFactoriesASC->push_back( wcf );
   } else {
      if ( !workClassFactoriesBI )
         workClassFactoriesBI = new WorkerClassList;

      workClassFactoriesBI->push_back( wcf );
   }
   return true;
}
