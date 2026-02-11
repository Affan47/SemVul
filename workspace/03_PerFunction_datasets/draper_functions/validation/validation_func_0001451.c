editToolbarAction (const QString & name,
                                                const char      code,
                                                const QString & shortText,
                                                const QString & text,
                                                const QString & toolTip,
                                                const QString & whatsThis)
{
    int mapCode = code;
    KToggleAction * ed = new KToggleAction (text, this);
    actionCollection()->addAction (name, ed);
    ed->setIconText (shortText);
    ed->setToolTip (toolTip);
    ed->setWhatsThis (whatsThis);
    connect (ed, SIGNAL (triggered(bool)), tempMapper, SLOT (map()));
    tempMapper->setMapping (ed, mapCode);
    return ed;
}
