void Converter::syncExifWithXmp()
    {
        Exiv2::XmpData::iterator td = xmpData_->findKey(XmpKey("Xmp.tiff.NativeDigest"));
        Exiv2::XmpData::iterator ed = xmpData_->findKey(XmpKey("Xmp.exif.NativeDigest"));
        if (td != xmpData_->end() && ed != xmpData_->end()) {
            if (td->value().toString() == computeExifDigest(true) &&
                ed->value().toString() == computeExifDigest(false)) {


                setOverwrite(true);
                setErase(false);

                cnvFromXmp();
                writeExifDigest();
                return;
            }
            else {


                setOverwrite(true);
                setErase(false);

                cnvToXmp();
                writeExifDigest();
                return;
            }
        }
        else {

            setOverwrite(false);
            setErase(false);

            cnvToXmp();
            writeExifDigest();
            return;
        }
    }
