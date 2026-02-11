enumeratePieceFiles(void)
	{

		for (size_t i = 0; i < mNumShaderTypes; i++)
		{
			mPieceFileNames[i].clear();
			mLoadedPieces[i].clear();
		}

		ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();

		for (size_t i = 0; i < mNumShaderTypes; ++i)
		{
			StringVecMap& pieceFileNames = mPieceFileNames[i];

			FileInfoListPtr list = rgm.findResourceFileInfo(mResorceGroup, "*_piece" + FilePatterns[i] + ".*");
			FileInfoList::iterator it = list->begin();
			FileInfoList::iterator end = list->end();

			for (; it != end; it++)
			{
				String name, ext;
				StringUtil::splitBaseFilename(it->filename, name, ext);

				StringVectorPtr namesVec;
				StringVecMap::iterator pieceFileNamesIt = pieceFileNames.find(ext);
				if (pieceFileNamesIt == pieceFileNames.end())
				{
					namesVec = StringVectorPtr(OGRE_NEW_T(StringVector, MEMCATEGORY_GENERAL)(), SPFM_DELETE_T);
					pieceFileNames[ext] = namesVec;
				}
				else
				{
					namesVec = pieceFileNames[ext];
				}

				namesVec->push_back(it->filename);
			}
		}
	}
