setBinaryDirectory(const QString& _dir)
{
  QString dir =
    QString::fromLocal8Bit(cmSystemTools::GetActualCaseForPath(_dir.toLocal8Bit().data()).c_str());
  if(this->BinaryDirectory != dir)
    {
    this->BinaryDirectory = QDir::fromNativeSeparators(dir);
    emit this->binaryDirChanged(this->BinaryDirectory);
    cmCacheManager *cachem = this->CMakeInstance->GetCacheManager();
    this->setGenerator(QString());
    if(!this->CMakeInstance->GetCacheManager()->LoadCache(
      this->BinaryDirectory.toLocal8Bit().data()))
      {
      QDir testDir(this->BinaryDirectory);
      if(testDir.exists("CMakeCache.txt"))
        {
        cmSystemTools::Error("There is a CMakeCache.txt file for the current binary "
            "tree but cmake does not have permission to read it.  "
            "Please check the permissions of the directory you are trying to run CMake on.");
        }
      }

    QCMakePropertyList props = this->properties();
    emit this->propertiesChanged(props);
    cmCacheManager::CacheIterator itm = cachem->NewIterator();
    if ( itm.Find("CMAKE_HOME_DIRECTORY"))
      {
      setSourceDirectory(QString::fromLocal8Bit(itm.GetValue()));
      }
    if ( itm.Find("CMAKE_GENERATOR"))
      {
      const char* extraGen = cachem->GetCacheValue("CMAKE_EXTRA_GENERATOR");
      std::string curGen = cmExternalMakefileProjectGenerator::
                              CreateFullGeneratorName(itm.GetValue(), extraGen);
      this->setGenerator(QString::fromLocal8Bit(curGen.c_str()));
      }
    }
}
