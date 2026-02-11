setIconset( const Iconset &is ) {
		setWindowTitle(caption().arg(is.name()));

		lb_name->setText(is.name());
		lb_version->setText(is.version());

		if ( is.description().isEmpty() ) {
			lb_desc->hide();
			lb_desc2->hide();
		}
		else
			lb_desc->setText(is.description());

		if ( !is.homeUrl().isEmpty() ) {
			lb_home->setTitle(is.homeUrl());
			lb_home->setUrl(is.homeUrl());
		}
		else {
			lb_home->hide();
			lb_home2->hide();
		}

		if ( is.creation().isEmpty() ) {
			lb_date->hide();
			lb_date2->hide();
		}
		else {
			QDate date = QDate::fromString(is.creation(), Qt::ISODate);
			lb_date->setText(date.toString(Qt::LocalDate));
		}

		if ( is.authors().count() == 0 ) {
			ptv_authors->hide();
			lb_authors->hide();
		}
		else {
			QString authors;
			QStringList::ConstIterator it = is.authors().begin();
			for ( ; it != is.authors().end(); ++it) {
				if ( !authors.isEmpty() )
					authors += "<br><br>";
				authors += *it;
			}
			ptv_authors->setText( "<qt><nobr>" + authors + "</nobr></qt>" );
		}

		isd_iconset->setIconset(is);

		resize(sizeHint());
	}
