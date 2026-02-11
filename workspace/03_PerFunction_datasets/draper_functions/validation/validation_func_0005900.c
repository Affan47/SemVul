drawSpecialBuildings(const char *key, const char *value, double default_height, const char *style, const char *roof_style) {
	list<MultiPolygon*> multipolygons;
	this->primitives.getMultiPolygonsWithAttribute(&multipolygons, key, value);
	for (list<MultiPolygon*>::iterator it = multipolygons.begin(); it != multipolygons.end(); it++) {
		const char *str;
		str = (*it)->getAttribute("layer");
		double extra_layer = (str == NULL ? 0 : atof(str)/500);
		if (extra_layer < 0) continue;

		double height = default_height;
		str = (*it)->getAttribute("building:levels");
		if (str != NULL) height = 4 + (atof(str)-1) * 3;
		str = (*it)->getAttribute("building:height");
		if (str == NULL) str = (*it)->getAttribute("height");
		if (str != NULL) height = readDimension(str);

		double min_height = 0;
		str = (*it)->getAttribute("min_height");
		if (str != NULL) {
			min_height = atof(str);
			extra_layer = 0;
		}

		{
			stringstream s;
			s << "Building " << (*it)->getId() << " (tag " << key;
			if (value != NULL) s << "=" << value;
			s << ")";
			this->pov_writer.writeComment(s.str().c_str());
		}

		this->drawBuilding(**it, min_height, height+extra_layer, style, roof_style);
		delete *it;
	}
}
