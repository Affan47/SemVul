MDFOutline(std::vector<Vector3>& mdfoutline) const
	{

		Orientation orient = MDFOrientation();


		if (orient == orient_invalid)
			return false;


		mdfoutline.resize(4);
		for (size_t corner_index = 0; corner_index < 4; corner_index++)
		{
			Outline[(corner_index + (size_t)orient) % 4].GetVector(mdfoutline[corner_index]);
		}


		return true;
	}
