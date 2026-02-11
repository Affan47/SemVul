event(QEvent *e)
{
	IconsetEmoUI *d = (IconsetEmoUI *)w;
	if ( e->type() == QEvent::User ) {
		IconsetLoadEvent *le = (IconsetLoadEvent *)e;

		if ( thread != le->thread() )
			return false;

		if ( !numIconsets )
			numIconsets = 1;
		d->progress->setValue( (int)((float)100 * ++iconsetsLoaded / numIconsets) );

		Iconset *is = le->iconset();
		if ( is ) {
			PsiIconset::removeAnimation(is);
			d->iss_emoticons->insert(*is);
			delete is;
		}

		return true;
	}
	else if ( e->type() == QEvent::User + 1 ) {
		d->ck_useEmoticons->setEnabled(true);
		d->ck_useEmoticons->unsetPalette();

		d->groupBox9->setEnabled(true);
		d->groupBox9->unsetPalette();

		connect(d->iss_emoticons, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), SIGNAL(dataChanged()));

		bool checked = d->ck_useEmoticons->isChecked();
		d->ck_useEmoticons->setChecked( true );
		d->ck_useEmoticons->setChecked( checked );

		d->progress->hide();

		d->unsetCursor();
		thread = 0;

		return true;
	}

	return false;
}
