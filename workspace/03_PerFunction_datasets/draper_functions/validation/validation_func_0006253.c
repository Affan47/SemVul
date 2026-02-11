RegisterBuiltInFactories()
{
  static SimpleMutexLock mutex;

    {
    static bool firstTime = true;


    MutexLockHolder< SimpleMutexLock > mutexHolder(mutex);
    if ( firstTime )
      {
      ObjectFactoryBase::RegisterFactory( BYUMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( FreeSurferAsciiMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( FreeSurferBinaryMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( GiftiMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( OBJMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( OFFMeshIOFactory::New() );
      ObjectFactoryBase::RegisterFactory( VTKPolyDataMeshIOFactory::New() );

      firstTime = false;
      }
    }
}
