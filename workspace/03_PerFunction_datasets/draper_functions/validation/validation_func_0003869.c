_ptrToObjRef(const char* id)
{
  if( id == ::CosLicensingManager::LicenseServiceManager::_PD_repoId )
    return (::CosLicensingManager::LicenseServiceManager_ptr) this;

  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::CosLicensingManager::LicenseServiceManager::_PD_repoId) )
    return (::CosLicensingManager::LicenseServiceManager_ptr) this;

  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}
