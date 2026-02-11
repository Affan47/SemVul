open(Mode mode, zlib_filefunc_def* ioApi)
{
  zipError=UNZ_OK;
  if(isOpen()) {
    qWarning("QuaZip::open(): ZIP already opened");
    return false;
  }
  switch(mode) {
    case mdUnzip:
      unzFile_f=unzOpen2(QFile::encodeName(zipName).constData(), ioApi);
      if(unzFile_f!=NULL) {
        this->mode=mode;
        return true;
      } else {
        zipError=UNZ_OPENERROR;
        return false;
      }
    case mdCreate:
    case mdAppend:
    case mdAdd:
      zipFile_f=zipOpen2(QFile::encodeName(zipName).constData(),
          mode==mdCreate?APPEND_STATUS_CREATE:
          mode==mdAppend?APPEND_STATUS_CREATEAFTER:
          APPEND_STATUS_ADDINZIP,
          NULL,
          ioApi);
      if(zipFile_f!=NULL) {
        this->mode=mode;
        return true;
      } else {
        zipError=UNZ_OPENERROR;
        return false;
      }
    default:
      qWarning("QuaZip::open(): unknown mode: %d", (int)mode);
      return false;
      break;
  }
}
