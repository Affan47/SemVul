initialize()
{
	int lastSys = mConfigFile->getLastSys();
	QStandardItemModel * model = new QStandardItemModel(0,1);
	model->clear();
	QStringList labels = (QStringList() << "Device");
	model->setHorizontalHeaderLabels(labels);
	QStandardItem *parentItem = model->invisibleRootItem();
	mDialogToFile.clear();

	outDebug(5, std::cout << "DeviceDlg::initilize from " <<lastSys+1 << " to " << mConfigFile->size() << std::endl);
	int lineNum=-1;
	for (int i=lastSys+1; i<mConfigFile->size(); i++)
	{
		const DeviceConfigLine * line = mConfigFile->getDevice(i);
		outDebug(5,std::cout <<"line=" << line->getLine() << line->isRemark() << std::endl);
		if (line->isRemark()) continue;

		std::string strLine = line->getToken(0);
		strLine.resize(10,' ');
		strLine += line->getToken(1).c_str();
		strLine.resize(20,' ');
		strLine += line->getMultiToken(2,0).c_str();
		strLine.resize(133,' ');
		QStandardItem * item = new QStandardItem(strLine.c_str());
		item->setIcon(DeviceTypes::instance().getIcon(line->getDeviceType()));

		parentItem->appendRow(item);
		++lineNum;
		mDialogToFile[lineNum] = i;
	}
	mConfigView->setModel(model);
	mConfigView->setColumnWidth(0,800);
	QFont font("Mono", 10);
	mConfigView->setFont(font);
	for (int i=0; i<model->rowCount(); i++)
		mConfigView->setRowHeight(i,18);
	mConfigView->setGridStyle(Qt::NoPen);
	mConfigView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
