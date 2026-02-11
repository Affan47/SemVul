slotCheckSpelling()
{
    if ( text().isEmpty() ) {
        return;
    }
    Sonnet::Dialog *spellDialog = new Sonnet::Dialog(new Sonnet::BackgroundChecker(this), 0);
    connect(spellDialog, SIGNAL(replace(QString,int,QString)), this, SLOT(spellCheckerCorrected(QString,int,QString)));
    connect(spellDialog, SIGNAL(misspelling(QString,int)), this, SLOT(spellCheckerMisspelling(QString,int)));
    connect(spellDialog, SIGNAL(done(QString)), this, SLOT(slotSpellCheckDone(QString)));
    connect(spellDialog, SIGNAL(cancel()), this, SLOT(spellCheckerFinished()));
    connect(spellDialog, SIGNAL(stop()), this, SLOT(spellCheckerFinished()));
    spellDialog->setBuffer(text());
    spellDialog->show();
}
