bool Utility::UnZip(const QString &zippath, const QString &destpath)
{
    int res = 0;
    QDir dir(destpath);
    if (!cp437) {
        cp437 = new QCodePage437Codec();
    }
#ifdef Q_OS_WIN32
    zlib_filefunc64_def ffunc;
    fill_win32_filefunc64W(&ffunc);
    unzFile zfile = unzOpen2_64(Utility::QStringToStdWString(QDir::toNativeSeparators(zippath)).c_str(), &ffunc);
#else
    unzFile zfile = unzOpen64(QDir::toNativeSeparators(zippath).toUtf8().constData());
#endif

    if ((zfile == NULL) || (!IsFileReadable(zippath)) || (!dir.exists())) {
        return false;
    }

    res = unzGoToFirstFile(zfile);

    if (res == UNZ_OK) {
        do {

            char file_name[MAX_PATH] = {0};
            unz_file_info64 file_info;
            unzGetCurrentFileInfo64(zfile, &file_info, file_name, MAX_PATH, NULL, 0, NULL, 0);
            QString qfile_name;
            QString cp437_file_name;
            qfile_name = QString::fromUtf8(file_name);
            if (!(file_info.flag & (1<<11))) {


                cp437_file_name = cp437->toUnicode(file_name);
            }


            if (!qfile_name.isEmpty()) {


	        QString original_path = qfile_name;
	        bool evil_or_corrupt_epub = false;

	        if (qfile_name.contains("\\")) evil_or_corrupt_epub = true;
	        qfile_name = "/" + qfile_name.replace("\\","");

	        if (qfile_name.contains("/../")) evil_or_corrupt_epub = true;
	        qfile_name = qfile_name.replace("/../","/");

	        while(qfile_name.startsWith("/")) {
		  qfile_name = qfile_name.remove(0,1);
	        }

	        if (cp437_file_name.contains("\\")) evil_or_corrupt_epub = true;
	        cp437_file_name = "/" + cp437_file_name.replace("\\","");

	        if (cp437_file_name.contains("/../")) evil_or_corrupt_epub = true;
	        cp437_file_name = cp437_file_name.replace("/../","/");

	        while(cp437_file_name.startsWith("/")) {
		  cp437_file_name = cp437_file_name.remove(0,1);
	        }

	        if (evil_or_corrupt_epub) {
		    unzCloseCurrentFile(zfile);
		    unzClose(zfile);

                    return false;
	        }


                QString file_path = destpath + "/" + qfile_name;
                QFileInfo qfile_info(file_path);


                if (file_info.uncompressed_size == 0 && qfile_name.endsWith('/')) {
                    dir.mkpath(qfile_name);
                    continue;
                } else {
                    dir.mkpath(qfile_info.path());
                }


                if (unzOpenCurrentFile(zfile) != UNZ_OK) {
                    unzClose(zfile);
                    return false;
                }


                QFile entry(file_path);

                if (!entry.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    unzCloseCurrentFile(zfile);
                    unzClose(zfile);
                    return false;
                }


                char buff[BUFF_SIZE] = {0};
                int read = 0;

                while ((read = unzReadCurrentFile(zfile, buff, BUFF_SIZE)) > 0) {
                    entry.write(buff, read);
                }

                entry.close();


                if (read < 0) {
                    unzCloseCurrentFile(zfile);
                    unzClose(zfile);
                    return false;
                }


                if (unzCloseCurrentFile(zfile) == UNZ_CRCERROR) {
                    unzClose(zfile);
                    return false;
                }

                if (!cp437_file_name.isEmpty() && cp437_file_name != qfile_name) {
                    QString cp437_file_path = destpath + "/" + cp437_file_name;
                    QFile::copy(file_path, cp437_file_path);
                }
            }
        } while ((res = unzGoToNextFile(zfile)) == UNZ_OK);
    }

    if (res != UNZ_END_OF_LIST_OF_FILE) {
        unzClose(zfile);
        return false;
    }

    unzClose(zfile);
    return true;
}
