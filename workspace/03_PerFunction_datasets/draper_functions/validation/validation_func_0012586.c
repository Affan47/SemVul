getMesh(const io::path& filename)
{
	IAnimatedMesh* msh = MeshCache->getMeshByName(filename);
	if (msh)
		return msh;

	io::IReadFile* file = FileSystem->createAndOpenFile(filename);
	if (!file)
	{
		os::Printer::log("Could not load mesh, because file could not be opened: ", filename, ELL_ERROR);
		return 0;
	}

	s32 count = MeshLoaderList.size();
	for (s32 i=count-1; i>=0; --i)
	{
		if (MeshLoaderList[i]->isALoadableFileExtension(filename))
		{

			file->seek(0);
			msh = MeshLoaderList[i]->createMesh(file);
			if (msh)
			{
				MeshCache->addMesh(filename, msh);
				msh->drop();
				break;
			}
		}
	}

	file->drop();

	if (!msh)
		os::Printer::log("Could not load mesh, file format seems to be unsupported", filename, ELL_ERROR);
	else
		os::Printer::log("Loaded mesh", filename, ELL_INFORMATION);

	return msh;
}
