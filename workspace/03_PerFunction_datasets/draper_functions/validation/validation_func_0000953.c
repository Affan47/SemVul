CheckShowItemInGivenCat(int inCategory)
{

	if (inCategory > 0 && inCategory != GetCategory()) {
		return false;
	}


	bool show = true;

	switch (thePrefs::GetAllcatFilter()) {
		case acfAllOthers:
			show = GetCategory() == 0 || inCategory > 0;
			break;
		case acfIncomplete:
			show = IsPartFile();
			break;
		case acfCompleted:
			show = !IsPartFile();
			break;
		case acfWaiting:
			show =
				(GetStatus() == PS_READY || GetStatus() == PS_EMPTY) &&
				GetTransferingSrcCount() == 0;
			break;
		case acfDownloading:
			show =
				(GetStatus() == PS_READY || GetStatus() == PS_EMPTY) &&
				GetTransferingSrcCount() > 0;
			break;
		case acfErroneous:
			show = GetStatus() == PS_ERROR;
			break;
		case acfPaused:
			show = GetStatus() == PS_PAUSED && !IsStopped();
			break;
		case acfStopped:
			show = IsStopped();
			break;
		case acfVideo:
			show = GetFiletype(GetFileName()) == ftVideo;
			break;
		case acfAudio:
			show = GetFiletype(GetFileName()) == ftAudio;
			break;
		case acfArchive:
			show = GetFiletype(GetFileName()) == ftArchive;
			break;
		case acfCDImages:
			show = GetFiletype(GetFileName()) == ftCDImage;
			break;
		case acfPictures:
			show = GetFiletype(GetFileName()) == ftPicture;
			break;
		case acfText:
			show = GetFiletype(GetFileName()) == ftText;
			break;
		case acfActive:
			show = !IsStopped() && GetStatus() != PS_PAUSED;
			break;
		default:
			show = true;
			break;
	}

	return show;
}
