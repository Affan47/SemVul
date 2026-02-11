slotOk()
{
	KSharedConfig::Ptr config = KGlobal::config();
	KConfigGroup configGroup(config->group(QString("New Game Dialog Mode")));

	configGroup.writeEntry("competition", mode->isChecked());
	if (enableCourses)
	{
		configGroup.writeEntry("course", currentCourse);
		configGroup.writeEntry("extra", externCourses);
	}

	config->deleteGroup("New Game Dialog");

	PlayerEditor *curEditor = 0;
	int i = 0;
	for (; i < editors.count(); ++i) {
		curEditor = editors.at(i);
		configGroup.writeEntry(QString::number(i) + curEditor->name(), curEditor->color().name());
	}

	config->sync();

	KDialog::accept();
}
