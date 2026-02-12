CStr2 CjfifDecode::LookupMakerCanonTag(unsigned nMainTag,unsigned nSubTag,unsigned nVal)
{
	CString		strTmp;
	CStr2		sRetVal;

	sRetVal.strTag = _T("???");
	sRetVal.bUnknown = false;
	sRetVal.strVal.Format(_T("%u"),nVal);

	unsigned nValHi,nValLo;
	nValHi = (nVal & 0xff00) >> 8;
	nValLo = (nVal & 0x00ff);

	switch(nMainTag)
	{

	case 0x0001:

		switch(nSubTag)
		{
		case 0x0001: sRetVal.strTag = _T("Canon.Cs1.Macro");break;
		case 0x0002: sRetVal.strTag = _T("Canon.Cs1.Selftimer");break;
		case 0x0003: sRetVal.strTag = _T("Canon.Cs1.Quality");
			if (nVal == 2) { sRetVal.strVal = _T("norm"); }
			else if (nVal == 3) { sRetVal.strVal = _T("fine"); }
			else if (nVal == 5) { sRetVal.strVal = _T("superfine"); }
			else {
				sRetVal.strVal = _T("?");
			}

			m_strImgQualExif = sRetVal.strVal;
			break;
		case 0x0004: sRetVal.strTag = _T("Canon.Cs1.FlashMode");break;
		case 0x0005: sRetVal.strTag = _T("Canon.Cs1.DriveMode");break;
		case 0x0007: sRetVal.strTag = _T("Canon.Cs1.FocusMode");
			switch(nVal) {
				case 0 : sRetVal.strVal = _T("One-shot");break;
				case 1 : sRetVal.strVal = _T("AI Servo");break;
				case 2 : sRetVal.strVal = _T("AI Focus");break;
				case 3 : sRetVal.strVal = _T("Manual Focus");break;
				case 4 : sRetVal.strVal = _T("Single");break;
				case 5 : sRetVal.strVal = _T("Continuous");break;
				case 6 : sRetVal.strVal = _T("Manual Focus");break;
				default : sRetVal.strVal = _T("?");break;
			}
			break;
		case 0x000a: sRetVal.strTag = _T("Canon.Cs1.ImageSize");
			if (nVal == 0) { sRetVal.strVal = _T("Large"); }
			else if (nVal == 1) { sRetVal.strVal = _T("Medium"); }
			else if (nVal == 2) { sRetVal.strVal = _T("Small"); }
			else {
				sRetVal.strVal = _T("?");
			}
			break;
		case 0x000b: sRetVal.strTag = _T("Canon.Cs1.EasyMode");break;
		case 0x000c: sRetVal.strTag = _T("Canon.Cs1.DigitalZoom");break;
		case 0x000d: sRetVal.strTag = _T("Canon.Cs1.Contrast");break;
		case 0x000e: sRetVal.strTag = _T("Canon.Cs1.Saturation");break;
		case 0x000f: sRetVal.strTag = _T("Canon.Cs1.Sharpness");break;
		case 0x0010: sRetVal.strTag = _T("Canon.Cs1.ISOSpeed");break;
		case 0x0011: sRetVal.strTag = _T("Canon.Cs1.MeteringMode");break;
		case 0x0012: sRetVal.strTag = _T("Canon.Cs1.FocusType");break;
		case 0x0013: sRetVal.strTag = _T("Canon.Cs1.AFPoint");break;
		case 0x0014: sRetVal.strTag = _T("Canon.Cs1.ExposureProgram");break;
		case 0x0016: sRetVal.strTag = _T("Canon.Cs1.LensType");break;
		case 0x0017: sRetVal.strTag = _T("Canon.Cs1.Lens");break;
		case 0x001a: sRetVal.strTag = _T("Canon.Cs1.MaxAperture");break;
		case 0x001b: sRetVal.strTag = _T("Canon.Cs1.MinAperture");break;
		case 0x001c: sRetVal.strTag = _T("Canon.Cs1.FlashActivity");break;
		case 0x001d: sRetVal.strTag = _T("Canon.Cs1.FlashDetails");break;
		case 0x0020: sRetVal.strTag = _T("Canon.Cs1.FocusMode");break;
		default:
			sRetVal.strTag.Format(_T("Canon.Cs1.x%04X"),nSubTag);
			sRetVal.bUnknown = true;
			break;
		}
		break;

	case 0x0004:

		switch(nSubTag)
		{
		case 0x0002: sRetVal.strTag = _T("Canon.Cs2.ISOSpeed");break;
		case 0x0004: sRetVal.strTag = _T("Canon.Cs2.TargetAperture");break;
		case 0x0005: sRetVal.strTag = _T("Canon.Cs2.TargetShutterSpeed");break;
		case 0x0007: sRetVal.strTag = _T("Canon.Cs2.WhiteBalance");break;
		case 0x0009: sRetVal.strTag = _T("Canon.Cs2.Sequence");break;
		case 0x000e: sRetVal.strTag = _T("Canon.Cs2.AFPointUsed");break;
		case 0x000f: sRetVal.strTag = _T("Canon.Cs2.FlashBias");break;
		case 0x0013: sRetVal.strTag = _T("Canon.Cs2.SubjectDistance");break;
		case 0x0015: sRetVal.strTag = _T("Canon.Cs2.ApertureValue");break;
		case 0x0016: sRetVal.strTag = _T("Canon.Cs2.ShutterSpeedValue");break;
		default:
			sRetVal.strTag.Format(_T("Canon.Cs2.x%04X"),nSubTag);
			sRetVal.bUnknown = true;
			break;
		}
		break;

	case 0x000F:


		sRetVal.strVal.Format(_T("%u"),nValLo);
		switch(nValHi)
		{

		case 0x0001: sRetVal.strTag = _T("Canon.Cf.NoiseReduction");break;
		case 0x0002: sRetVal.strTag = _T("Canon.Cf.ShutterAeLock");break;
		case 0x0003: sRetVal.strTag = _T("Canon.Cf.MirrorLockup");break;
		case 0x0004: sRetVal.strTag = _T("Canon.Cf.ExposureLevelIncrements");break;
		case 0x0005: sRetVal.strTag = _T("Canon.Cf.AFAssist");break;
		case 0x0006: sRetVal.strTag = _T("Canon.Cf.FlashSyncSpeedAv");break;
		case 0x0007: sRetVal.strTag = _T("Canon.Cf.AEBSequence");break;
		case 0x0008: sRetVal.strTag = _T("Canon.Cf.ShutterCurtainSync");break;
		case 0x0009: sRetVal.strTag = _T("Canon.Cf.LensAFStopButton");break;
		case 0x000a: sRetVal.strTag = _T("Canon.Cf.FillFlashAutoReduction");break;
		case 0x000b: sRetVal.strTag = _T("Canon.Cf.MenuButtonReturn");break;
		case 0x000c: sRetVal.strTag = _T("Canon.Cf.SetButtonFunction");break;
		case 0x000d: sRetVal.strTag = _T("Canon.Cf.SensorCleaning");break;
		case 0x000e: sRetVal.strTag = _T("Canon.Cf.SuperimposedDisplay");break;
		case 0x000f: sRetVal.strTag = _T("Canon.Cf.ShutterReleaseNoCFCard");break;
		default:
			sRetVal.strTag.Format(_T("Canon.Cf.x%04X"),nValHi);
			sRetVal.bUnknown = true;
			break;
		}
		break;


	case 0x0012:

		switch(nSubTag)
		{
		case 0x0002: sRetVal.strTag = _T("Canon.Pi.ImageWidth");break;
		case 0x0003: sRetVal.strTag = _T("Canon.Pi.ImageHeight");break;
		case 0x0004: sRetVal.strTag = _T("Canon.Pi.ImageWidthAsShot");break;
		case 0x0005: sRetVal.strTag = _T("Canon.Pi.ImageHeightAsShot");break;
		case 0x0016: sRetVal.strTag = _T("Canon.Pi.AFPointsUsed");break;
		case 0x001a: sRetVal.strTag = _T("Canon.Pi.AFPointsUsed20D");break;
		default:
			sRetVal.strTag.Format(_T("Canon.Pi.x%04X"),nSubTag);
			sRetVal.bUnknown = true;
			break;
		}
		break;

	default:
		sRetVal.strTag.Format(_T("Canon.x%04X.x%04X"),nMainTag,nSubTag);
		sRetVal.bUnknown = true;
		break;

	}

	return sRetVal;
}
