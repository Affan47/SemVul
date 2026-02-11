readSparseValues(istringstream& ss, vector<FeatureReal>& values,
									  vector<int>& idxs, map<int, int>& idxmap, vector<NameMap>& enumMaps,
									  const vector<RawData::eAttributeType>& attributeTypes)
	{
		string tmpVal;
		int tmpIdx;
		int i = 0;
		int labelFeatureIndex = attributeTypes.size();
		while (!ss.eof())
		{
			ss >> tmpIdx;

			if (tmpIdx == labelFeatureIndex ) break;

			idxs.push_back(tmpIdx);
			idxmap[ tmpIdx ] = i++;
			ss >> tmpVal;
			if ( attributeTypes[tmpIdx] == RawData::ATTRIBUTE_NUMERIC )
			{
				FeatureReal val;
				stringstream ss;
				ss.str(tmpVal);
				ss >> val;
				values.push_back( val );
			} else  {
				values.push_back( enumMaps[tmpIdx].getIdxFromName(tmpVal) );
			}
		}
	}
