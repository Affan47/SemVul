setSetting( BatchSettingId id, bool value, const String &materialName )
    {
        assert( id < NUM_SETTINGS );

        if( materialName == BLANKSTRING )
        {

            InstanceBatchMap::iterator itor = mInstanceBatches.begin();
            InstanceBatchMap::iterator end  = mInstanceBatches.end();

            while( itor != end )
            {
                mBatchSettings[itor->first].setting[id] = value;
                applySettingToBatches( id, value, itor->second );

                ++itor;
            }
        }
        else
        {

            mBatchSettings[materialName].setting[id] = value;

            InstanceBatchMap::const_iterator itor = mInstanceBatches.find( materialName );

            if( itor != mInstanceBatches.end() )
                applySettingToBatches( id, value, itor->second );
        }
    }
