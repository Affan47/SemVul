CString CjfifDecode::LookupExifTag(CString strSect,unsigned nTag,bool &bUnknown)
{
	CString strTmp;
	bUnknown = false;

	if (strSect == _T("IFD0"))
	{

		switch(nTag)
		{

		case 0x010E: return _T("ImageDescription");break;
		case 0x010F: return _T("Make");break;
		case 0x0110: return _T("Model");break;
		case 0x0112: return _T("Orientation");break;
		case 0x011A: return _T("XResolution");break;
		case 0x011B: return _T("YResolution");break;
		case 0x0128: return _T("ResolutionUnit");break;
		case 0x0131: return _T("Software");break;
		case 0x0132: return _T("DateTime");break;
		case 0x013B: return _T("Artist");break;
		case 0x013E: return _T("WhitePoint");break;
		case 0x013F: return _T("PrimChromaticities");break;
		case 0x0211: return _T("YCbCrCoefficients");break;
		case 0x0213: return _T("YCbCrPositioning");break;
		case 0x0214: return _T("ReferenceBlackWhite");break;
		case 0x8298: return _T("Copyright");break;
		case 0x8769: return _T("ExifOffset");break;
		case 0x8825: return _T("GPSOffset");break;

		case 0x9C9B: return _T("XPTitle");break;
		case 0x9C9C: return _T("XPComment");break;
		case 0x9C9D: return _T("XPAuthor");break;
		case 0x9C9e: return _T("XPKeywords");break;
		case 0x9C9f: return _T("XPSubject");break;

		case 0xA401: return _T("CustomRendered");break;
		case 0xA402: return _T("ExposureMode");break;
		case 0xA403: return _T("WhiteBalance");break;
		case 0xA406: return _T("SceneCaptureType");break;

		default:
			strTmp.Format(_T("IFD0.0x%04X"),nTag);
			bUnknown = true;
			return strTmp;
			break;
		}

	} else if (strSect == _T("SubIFD")) {

		switch(nTag)
		{
		case 0x00fe: return _T("NewSubfileType");break;
		case 0x00ff: return _T("SubfileType");break;
		case 0x012d: return _T("TransferFunction");break;
		case 0x013b: return _T("Artist");break;
		case 0x013d: return _T("Predictor");break;
		case 0x0142: return _T("TileWidth");break;
		case 0x0143: return _T("TileLength");break;
		case 0x0144: return _T("TileOffsets");break;
		case 0x0145: return _T("TileByteCounts");break;
		case 0x014a: return _T("SubIFDs");break;
		case 0x015b: return _T("JPEGTables");break;
		case 0x828d: return _T("CFARepeatPatternDim");break;
		case 0x828e: return _T("CFAPattern");break;
		case 0x828f: return _T("BatteryLevel");break;
		case 0x829A: return _T("ExposureTime");break;
		case 0x829D: return _T("FNumber");break;
		case 0x83bb: return _T("IPTC/NAA");break;
		case 0x8773: return _T("InterColorProfile");break;
		case 0x8822: return _T("ExposureProgram");break;
		case 0x8824: return _T("SpectralSensitivity");break;
		case 0x8825: return _T("GPSInfo");break;
		case 0x8827: return _T("ISOSpeedRatings");break;
		case 0x8828: return _T("OECF");break;
		case 0x8829: return _T("Interlace");break;
		case 0x882a: return _T("TimeZoneOffset");break;
		case 0x882b: return _T("SelfTimerMode");break;
		case 0x9000: return _T("ExifVersion");break;
		case 0x9003: return _T("DateTimeOriginal");break;
		case 0x9004: return _T("DateTimeDigitized");break;
		case 0x9101: return _T("ComponentsConfiguration");break;
		case 0x9102: return _T("CompressedBitsPerPixel");break;
		case 0x9201: return _T("ShutterSpeedValue");break;
		case 0x9202: return _T("ApertureValue");break;
		case 0x9203: return _T("BrightnessValue");break;
		case 0x9204: return _T("ExposureBiasValue");break;
		case 0x9205: return _T("MaxApertureValue");break;
		case 0x9206: return _T("SubjectDistance");break;
		case 0x9207: return _T("MeteringMode");break;
		case 0x9208: return _T("LightSource");break;
		case 0x9209: return _T("Flash");break;
		case 0x920A: return _T("FocalLength");break;
		case 0x920b: return _T("FlashEnergy");break;
		case 0x920c: return _T("SpatialFrequencyResponse");break;
		case 0x920d: return _T("Noise");break;
		case 0x9211: return _T("ImageNumber");break;
		case 0x9212: return _T("SecurityClassification");break;
		case 0x9213: return _T("ImageHistory");break;
		case 0x9214: return _T("SubjectLocation");break;
		case 0x9215: return _T("ExposureIndex");break;
		case 0x9216: return _T("TIFF/EPStandardID");break;
		case 0x927C: return _T("MakerNote");break;
		case 0x9286: return _T("UserComment");break;
		case 0x9290: return _T("SubSecTime");break;
		case 0x9291: return _T("SubSecTimeOriginal");break;
		case 0x9292: return _T("SubSecTimeDigitized");break;
		case 0xA000: return _T("FlashPixVersion");break;
		case 0xA001: return _T("ColorSpace");break;
		case 0xA002: return _T("ExifImageWidth");break;
		case 0xA003: return _T("ExifImageHeight");break;
		case 0xA004: return _T("RelatedSoundFile");break;
		case 0xA005: return _T("ExifInteroperabilityOffset");break;
		case 0xa20b: return _T("FlashEnergy  unsigned");break;
		case 0xa20c: return _T("SpatialFrequencyResponse");break;
		case 0xA20E: return _T("FocalPlaneXResolution");break;
		case 0xA20F: return _T("FocalPlaneYResolution");break;
		case 0xA210: return _T("FocalPlaneResolutionUnit");break;
		case 0xa214: return _T("SubjectLocation");break;
		case 0xa215: return _T("ExposureIndex");break;
		case 0xA217: return _T("SensingMethod");break;
		case 0xA300: return _T("FileSource");break;
		case 0xA301: return _T("SceneType");break;
		case 0xa302: return _T("CFAPattern");break;
		case 0xa401: return _T("CustomRendered");break;
		case 0xa402: return _T("ExposureMode");break;
		case 0xa403: return _T("WhiteBalance");break;
		case 0xa404: return _T("DigitalZoomRatio");break;
		case 0xa405: return _T("FocalLengthIn35mmFilm");break;
		case 0xa406: return _T("SceneCaptureType");break;
		case 0xa407: return _T("GainControl");break;
		case 0xa408: return _T("Contrast");break;
		case 0xa409: return _T("Saturation");break;
		case 0xa40a: return _T("Sharpness");break;
		case 0xa40b: return _T("DeviceSettingDescription");break;
		case 0xa40c: return _T("SubjectDistanceRange");break;
		case 0xa420: return _T("ImageUniqueID");break;

		default:
			strTmp.Format(_T("SubIFD.0x%04X"),nTag);
			bUnknown = true;
			return strTmp;
			break;

		}

	} else if (strSect == _T("IFD1")) {

		switch(nTag)
		{
		case 0x0100: return _T("ImageWidth");break;
		case 0x0101: return _T("ImageLength");break;
		case 0x0102: return _T("BitsPerSample");break;
		case 0x0103: return _T("Compression");break;
		case 0x0106: return _T("PhotometricInterpretation");break;
		case 0x0111: return _T("StripOffsets");break;
		case 0x0115: return _T("SamplesPerPixel");break;
		case 0x0116: return _T("RowsPerStrip");break;
		case 0x0117: return _T("StripByteConunts");break;
		case 0x011a: return _T("XResolution");break;
		case 0x011b: return _T("YResolution");break;
		case 0x011c: return _T("PlanarConfiguration");break;
		case 0x0128: return _T("ResolutionUnit");break;
		case 0x0201: return _T("JpegIFOffset");break;
		case 0x0202: return _T("JpegIFByteCount");break;
		case 0x0211: return _T("YCbCrCoefficients");break;
		case 0x0212: return _T("YCbCrSubSampling");break;
		case 0x0213: return _T("YCbCrPositioning");break;
		case 0x0214: return _T("ReferenceBlackWhite");break;

		default:
			strTmp.Format(_T("IFD1.0x%04X"),nTag);
			bUnknown = true;
			return strTmp;
			break;

		}

	} else if (strSect == _T("InteropIFD")) {
		switch(nTag) {
			case 0x0001: return _T("InteroperabilityIndex");break;
			case 0x0002: return _T("InteroperabilityVersion");break;
			case 0x1000: return _T("RelatedImageFileFormat");break;
			case 0x1001: return _T("RelatedImageWidth");break;
			case 0x1002: return _T("RelatedImageLength");break;

			default:
				strTmp.Format(_T("Interop.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
		}
	} else if (strSect == _T("GPSIFD")) {
		switch(nTag) {
			case 0x0000: return _T("GPSVersionID");break;
			case 0x0001: return _T("GPSLatitudeRef");break;
			case 0x0002: return _T("GPSLatitude");break;
			case 0x0003: return _T("GPSLongitudeRef");break;
			case 0x0004: return _T("GPSLongitude");break;
			case 0x0005: return _T("GPSAltitudeRef");break;
			case 0x0006: return _T("GPSAltitude");break;
			case 0x0007: return _T("GPSTimeStamp");break;
			case 0x0008: return _T("GPSSatellites");break;
			case 0x0009: return _T("GPSStatus");break;
			case 0x000A: return _T("GPSMeasureMode");break;
			case 0x000B: return _T("GPSDOP");break;
			case 0x000C: return _T("GPSSpeedRef");break;
			case 0x000D: return _T("GPSSpeed");break;
			case 0x000E: return _T("GPSTrackRef");break;
			case 0x000F: return _T("GPSTrack");break;
			case 0x0010: return _T("GPSImgDirectionRef");break;
			case 0x0011: return _T("GPSImgDirection");break;
			case 0x0012: return _T("GPSMapDatum");break;
			case 0x0013: return _T("GPSDestLatitudeRef");break;
			case 0x0014: return _T("GPSDestLatitude");break;
			case 0x0015: return _T("GPSDestLongitudeRef");break;
			case 0x0016: return _T("GPSDestLongitude");break;
			case 0x0017: return _T("GPSDestBearingRef");break;
			case 0x0018: return _T("GPSDestBearing");break;
			case 0x0019: return _T("GPSDestDistanceRef");break;
			case 0x001A: return _T("GPSDestDistance");break;
			case 0x001B: return _T("GPSProcessingMethod");break;
			case 0x001C: return _T("GPSAreaInformation");break;
			case 0x001D: return _T("GPSDateStamp");break;
			case 0x001E: return _T("GPSDifferential");break;

			default:
				strTmp.Format(_T("GPS.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
		}
	} else if (strSect == _T("MakerIFD")) {


		if (m_strImgExifMake == _T("Canon")) {

			switch(nTag)
			{
			case 0x0001: return _T("Canon.CameraSettings1");break;
			case 0x0004: return _T("Canon.CameraSettings2");break;
			case 0x0006: return _T("Canon.ImageType");break;
			case 0x0007: return _T("Canon.FirmwareVersion");break;
			case 0x0008: return _T("Canon.ImageNumber");break;
			case 0x0009: return _T("Canon.OwnerName");break;
			case 0x000C: return _T("Canon.SerialNumber");break;
			case 0x000F: return _T("Canon.CustomFunctions");break;
			case 0x0012: return _T("Canon.PictureInfo");break;
			case 0x00A9: return _T("Canon.WhiteBalanceTable");break;

			default:
				strTmp.Format(_T("Canon.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
			}

		}

		else if (m_strImgExifMake == _T("SIGMA"))
		{
			switch(nTag)
			{
			case 0x0002: return _T("Sigma.SerialNumber");break;
			case 0x0003: return _T("Sigma.DriveMode");break;
			case 0x0004: return _T("Sigma.ResolutionMode");break;
			case 0x0005: return _T("Sigma.AutofocusMode");break;
			case 0x0006: return _T("Sigma.FocusSetting");break;
			case 0x0007: return _T("Sigma.WhiteBalance");break;
			case 0x0008: return _T("Sigma.ExposureMode");break;
			case 0x0009: return _T("Sigma.MeteringMode");break;
			case 0x000a: return _T("Sigma.LensRange");break;
			case 0x000b: return _T("Sigma.ColorSpace");break;
			case 0x000c: return _T("Sigma.Exposure");break;
			case 0x000d: return _T("Sigma.Contrast");break;
			case 0x000e: return _T("Sigma.Shadow");break;
			case 0x000f: return _T("Sigma.Highlight");break;
			case 0x0010: return _T("Sigma.Saturation");break;
			case 0x0011: return _T("Sigma.Sharpness");break;
			case 0x0012: return _T("Sigma.FillLight");break;
			case 0x0014: return _T("Sigma.ColorAdjustment");break;
			case 0x0015: return _T("Sigma.AdjustmentMode");break;
			case 0x0016: return _T("Sigma.Quality");break;
			case 0x0017: return _T("Sigma.Firmware");break;
			case 0x0018: return _T("Sigma.Software");break;
			case 0x0019: return _T("Sigma.AutoBracket");break;
			default:
				strTmp.Format(_T("Sigma.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
			}
		}

		else if (m_strImgExifMake == _T("SONY"))
		{

			switch(nTag)
			{
			case 0xb021: return _T("Sony.ColorTemperature");break;
			case 0xb023: return _T("Sony.SceneMode");break;
			case 0xb024: return _T("Sony.ZoneMatching");break;
			case 0xb025: return _T("Sony.DynamicRangeOptimizer");break;
			case 0xb026: return _T("Sony.ImageStabilization");break;
			case 0xb027: return _T("Sony.LensID");break;
			case 0xb029: return _T("Sony.ColorMode");break;
			case 0xb040: return _T("Sony.Macro");break;
			case 0xb041: return _T("Sony.ExposureMode");break;
			case 0xb047: return _T("Sony.Quality");break;
			case 0xb04e: return _T("Sony.LongExposureNoiseReduction");break;
			default:

				strTmp.Format(_T("Sony.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
			}
		}

		else if (m_strImgExifMake == _T("FUJIFILM"))
		{
			switch(nTag)
			{
			case 0x0000: return _T("Fujifilm.Version");break;
			case 0x1000: return _T("Fujifilm.Quality");break;
			case 0x1001: return _T("Fujifilm.Sharpness");break;
			case 0x1002: return _T("Fujifilm.WhiteBalance");break;
			case 0x1003: return _T("Fujifilm.Color");break;
			case 0x1004: return _T("Fujifilm.Tone");break;
			case 0x1010: return _T("Fujifilm.FlashMode");break;
			case 0x1011: return _T("Fujifilm.FlashStrength");break;
			case 0x1020: return _T("Fujifilm.Macro");break;
			case 0x1021: return _T("Fujifilm.FocusMode");break;
			case 0x1030: return _T("Fujifilm.SlowSync");break;
			case 0x1031: return _T("Fujifilm.PictureMode");break;
			case 0x1100: return _T("Fujifilm.Continuous");break;
			case 0x1210: return _T("Fujifilm.FinePixColor");break;
			case 0x1300: return _T("Fujifilm.BlurWarning");break;
			case 0x1301: return _T("Fujifilm.FocusWarning");break;
			case 0x1302: return _T("Fujifilm.AeWarning");break;
			default:
				strTmp.Format(_T("Fujifilm.0x%04X"),nTag);
				bUnknown = true;
				return strTmp;
				break;
			}
		}

		else if (m_strImgExifMake == _T("NIKON"))
		{
			if (m_nImgExifMakeSubtype == 1) {

				switch(nTag)
				{
				case 0x0001: return _T("Nikon1.Version");break;
				case 0x0002: return _T("Nikon1.ISOSpeed");break;
				case 0x0003: return _T("Nikon1.ColorMode");break;
				case 0x0004: return _T("Nikon1.Quality");break;
				case 0x0005: return _T("Nikon1.WhiteBalance");break;
				case 0x0006: return _T("Nikon1.Sharpening");break;
				case 0x0007: return _T("Nikon1.Focus");break;
				case 0x0008: return _T("Nikon1.Flash");break;
				case 0x000f: return _T("Nikon1.ISOSelection");break;
				case 0x0010: return _T("Nikon1.DataDump");break;
				case 0x0080: return _T("Nikon1.ImageAdjustment");break;
				case 0x0082: return _T("Nikon1.Adapter");break;
				case 0x0085: return _T("Nikon1.FocusDistance");break;
				case 0x0086: return _T("Nikon1.DigitalZoom");break;
				case 0x0088: return _T("Nikon1.AFFocusPos");break;
				default:
					strTmp.Format(_T("Nikon1.0x%04X"),nTag);
					bUnknown = true;
					return strTmp;
					break;
				}
			}
			else if (m_nImgExifMakeSubtype == 2)
			{

				switch(nTag)
				{
				case 0x0003: return _T("Nikon2.Quality");break;
				case 0x0004: return _T("Nikon2.ColorMode");break;
				case 0x0005: return _T("Nikon2.ImageAdjustment");break;
				case 0x0006: return _T("Nikon2.ISOSpeed");break;
				case 0x0007: return _T("Nikon2.WhiteBalance");break;
				case 0x0008: return _T("Nikon2.Focus");break;
				case 0x000a: return _T("Nikon2.DigitalZoom");break;
				case 0x000b: return _T("Nikon2.Adapter");break;
				default:
					strTmp.Format(_T("Nikon2.0x%04X"),nTag);
					bUnknown = true;
					return strTmp;
					break;
				}
			}
			else if (m_nImgExifMakeSubtype == 3)
			{

				switch(nTag)
				{
				case 0x0001: return _T("Nikon3.Version");break;
				case 0x0002: return _T("Nikon3.ISOSpeed");break;
				case 0x0003: return _T("Nikon3.ColorMode");break;
				case 0x0004: return _T("Nikon3.Quality");break;
				case 0x0005: return _T("Nikon3.WhiteBalance");break;
				case 0x0006: return _T("Nikon3.Sharpening");break;
				case 0x0007: return _T("Nikon3.Focus");break;
				case 0x0008: return _T("Nikon3.FlashSetting");break;
				case 0x0009: return _T("Nikon3.FlashMode");break;
				case 0x000b: return _T("Nikon3.WhiteBalanceBias");break;
				case 0x000e: return _T("Nikon3.ExposureDiff");break;
				case 0x000f: return _T("Nikon3.ISOSelection");break;
				case 0x0010: return _T("Nikon3.DataDump");break;
				case 0x0011: return _T("Nikon3.ThumbOffset");break;
				case 0x0012: return _T("Nikon3.FlashComp");break;
				case 0x0013: return _T("Nikon3.ISOSetting");break;
				case 0x0016: return _T("Nikon3.ImageBoundary");break;
				case 0x0018: return _T("Nikon3.FlashBracketComp");break;
				case 0x0019: return _T("Nikon3.ExposureBracketComp");break;
				case 0x0080: return _T("Nikon3.ImageAdjustment");break;
				case 0x0081: return _T("Nikon3.ToneComp");break;
				case 0x0082: return _T("Nikon3.AuxiliaryLens");break;
				case 0x0083: return _T("Nikon3.LensType");break;
				case 0x0084: return _T("Nikon3.Lens");break;
				case 0x0085: return _T("Nikon3.FocusDistance");break;
				case 0x0086: return _T("Nikon3.DigitalZoom");break;
				case 0x0087: return _T("Nikon3.FlashType");break;
				case 0x0088: return _T("Nikon3.AFFocusPos");break;
				case 0x0089: return _T("Nikon3.Bracketing");break;
				case 0x008b: return _T("Nikon3.LensFStops");break;
				case 0x008c: return _T("Nikon3.ToneCurve");break;
				case 0x008d: return _T("Nikon3.ColorMode");break;
				case 0x008f: return _T("Nikon3.SceneMode");break;
				case 0x0090: return _T("Nikon3.LightingType");break;
				case 0x0092: return _T("Nikon3.HueAdjustment");break;
				case 0x0094: return _T("Nikon3.Saturation");break;
				case 0x0095: return _T("Nikon3.NoiseReduction");break;
				case 0x0096: return _T("Nikon3.CompressionCurve");break;
				case 0x0097: return _T("Nikon3.ColorBalance2");break;
				case 0x0098: return _T("Nikon3.LensData");break;
				case 0x0099: return _T("Nikon3.NEFThumbnailSize");break;
				case 0x009a: return _T("Nikon3.SensorPixelSize");break;
				case 0x00a0: return _T("Nikon3.SerialNumber");break;
				case 0x00a7: return _T("Nikon3.ShutterCount");break;
				case 0x00a9: return _T("Nikon3.ImageOptimization");break;
				case 0x00aa: return _T("Nikon3.Saturation");break;
				case 0x00ab: return _T("Nikon3.VariProgram");break;

				default:
					strTmp.Format(_T("Nikon3.0x%04X"),nTag);
					bUnknown = true;
					return strTmp;
					break;
				}

			}
		}

	}

	bUnknown = true;
	return _T("???");
}
