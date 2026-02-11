readDenseValues(Bzip2WrapperReader& in, vector<FeatureReal>& values,
		vector<NameMap>& enumMaps,
		const vector<RawData::eAttributeType>& attributeTypes )
	{


		values.reserve(_numAttributes);
		string tmpVal;

		for ( int j = 0; j < _numAttributes; ++j )
		{
			in >> tmpVal;
			if ( attributeTypes[j] == RawData::ATTRIBUTE_NUMERIC )
				if ( ( ! tmpVal.compare( "NaN" ) ) || ( ! tmpVal.compare( "?" ) ) )
					values.push_back( numeric_limits<FeatureReal>::infinity() );
				else
					values.push_back(atof(tmpVal.c_str()));
			else
				values.push_back( enumMaps[j].getIdxFromName(tmpVal) );
		}


	}
