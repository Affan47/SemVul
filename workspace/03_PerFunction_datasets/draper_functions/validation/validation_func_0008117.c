ParseXml(QXmlStreamReader& xml)
{
	bool foundManufacturer = false;
	bool foundProduct = false;
	bool foundName = false;

	while (!xml.atEnd())
	{
		QXmlStreamReader::TokenType nextToken = xml.readNext();

		if (nextToken == QXmlStreamReader::StartElement)
		{
			if (xml.name() == "manufacturer")
			{
				if (foundManufacturer)
				{
					Alerts::DisplayError("Found multiple <manufacturer> elements in <device>.");
					return (false);
				}

				foundManufacturer = true;

				manufacturer = xml.readElementText();
			}
			else if (xml.name() == "product")
			{
				if (foundProduct)
				{
					Alerts::DisplayError("Found multiple <product> elements in <device>.");
					return (false);
				}

				foundProduct = true;

				product = xml.readElementText();
			}
			else if (xml.name() == "name")
			{
				if (foundName)
				{
					Alerts::DisplayError("Found multiple <name> elements in <device>.");
					return (false);
				}

				foundName = true;

				name = xml.readElementText();
			}
			else
			{
				Alerts::DisplayError(QString("<%1> is not a valid child of <device>.").arg(xml.name().toString()));
				return (false);
			}
		}
		else if (nextToken == QXmlStreamReader::EndElement)
		{
			if (xml.name() == "device")
			{
				if (foundManufacturer && foundProduct && foundName)
				{
					return (true);
				}
				else
				{
					Alerts::DisplayError("Required elements are missing from <device>.");
					return (false);
				}
			}
		}
		else
		{
			if (!(nextToken == QXmlStreamReader::Characters && xml.isWhitespace()))
			{
				Alerts::DisplayError("Unexpected token found in <device>.");
				return (false);
			}
		}
	}

	return (false);
}
