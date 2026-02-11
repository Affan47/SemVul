retrieveModuleId(const QString &family, const QMultiHash<QString, QString> &properties, const QString &propertyName, bool closestMatch)
{
	QString propertyValue;

	if(properties.size() > 0) {
		QString queryStr =
			"SELECT moduleID FROM parts part \n"
			"WHERE part.family = :family AND (1=1 ";
		QHash<QString, QString> params;
        int ix = 0;
		foreach (QString name, properties.uniqueKeys()) {
            foreach (QString value, properties.values(name)) {
			    QString propParam = QString(":prop%1").arg(ix++);
			    queryStr += QString(" AND EXISTS (SELECT * FROM properties prop WHERE prop.part_id = part.id AND prop.name = %1_name AND prop.value = %1_value)").arg(propParam);
			    params[propParam+"_name"] = name;
			    params[propParam+"_value"] = value;
			    if(name == propertyName) {
				    propertyValue = value;
			    }
            }
		}
		queryStr += ") order by part.core desc";

		QSqlQuery query;
		query.prepare(queryStr);

		query.bindValue(":family",family.toLower().trimmed());
		foreach(QString name, params.uniqueKeys()) {
			query.bindValue(name,params[name].toLower().trimmed());
		}

		QString moduleId;
		if(query.exec()) {
			if(query.next()) {
				moduleId =  query.value(0).toString();
			}

		} else {
            debugExec("couldn't retrieve part", query);
		}

		if(!moduleId.isEmpty()) {
			m_lastWasExactMatch = true;
			return moduleId;
		} else if(closestMatch || !propertyName.isEmpty()) {
			m_lastWasExactMatch = false;
			return closestMatchId(family, properties, propertyName, propertyValue);
		} else {
			return ___emptyString___;
		}
	} else {
		return ___emptyString___;
	}
}
