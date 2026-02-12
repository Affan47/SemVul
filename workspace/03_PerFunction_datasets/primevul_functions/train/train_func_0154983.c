void ImportEPUB::ReadOPF()
{
    QString opf_text = CleanSource::ProcessXML(PrepareOPFForReading(Utility::ReadUnicodeTextFile(m_OPFFilePath)),OEBPS_MIMETYPE);
    QXmlStreamReader opf_reader(opf_text);
    QString ncx_id_on_spine;

    while (!opf_reader.atEnd()) {
        opf_reader.readNext();

        if (!opf_reader.isStartElement()) {
            continue;
        }

        if (opf_reader.name() == "package") {
            m_UniqueIdentifierId = opf_reader.attributes().value("", "unique-identifier").toString();
            m_PackageVersion = opf_reader.attributes().value("", "version").toString();
            if (m_PackageVersion == "1.0") m_PackageVersion = "2.0";
	}

        else if (opf_reader.name() == "identifier") {
            ReadIdentifierElement(&opf_reader);
	}


        else if (opf_reader.name() == "link") {
            ReadMetadataLinkElement(&opf_reader);
	}


        else if (opf_reader.name() == "item") {
            ReadManifestItemElement(&opf_reader);
        }


        else if (opf_reader.name() == "spine") {
            ncx_id_on_spine = opf_reader.attributes().value("", "toc").toString();
        }

        else if (opf_reader.name() == "itemref") {
            m_HasSpineItems = true;
        }
    }

    if (opf_reader.hasError()) {
        const QString error = QString(QObject::tr("Unable to read OPF file.\nLine: %1 Column %2 - %3"))
                              .arg(opf_reader.lineNumber())
                              .arg(opf_reader.columnNumber())
                              .arg(opf_reader.errorString());
        throw (EPUBLoadParseError(error.toStdString()));
    }


    LocateOrCreateNCX(ncx_id_on_spine);

}
