ptp_unpack_CANON_changes (PTPParams *params, unsigned char* data, int datasize, PTPCanon_changes_entry **pce)
{
	int	i = 0, entries = 0;
	unsigned char	*curdata = data;
	PTPCanon_changes_entry *ce;

	if (data==NULL)
		return 0;
	while (curdata - data + 8 < datasize) {
		uint32_t	size = dtoh32a(&curdata[PTP_ece_Size]);
		uint32_t	type = dtoh32a(&curdata[PTP_ece_Type]);

		if (size > datasize) {
			ptp_debug (params, "size %d is larger than datasize %d", size, datasize);
			break;
		}
		if (size < 8) {
			ptp_debug (params, "size %d is smaller than 8.", size);
			break;
		}
		if ((size == 8) && (type == 0))
			break;
		if ((curdata - data) + size >= datasize) {
			ptp_debug (params, "canon eos event decoder ran over supplied data, skipping entries");
			break;
		}
		if (type == PTP_EC_CANON_EOS_OLCInfoChanged) {
			unsigned int j;

			entries++;
			if (size >= 12+2) {
				for (j=0;j<31;j++)
					if (dtoh16a(curdata+12) & (1<<j))
						entries++;
			}
		}
		curdata += size;
		entries++;
	}
	ce = malloc (sizeof(PTPCanon_changes_entry)*(entries+1));
	if (!ce) return 0;

	curdata = data;
	while (curdata - data  + 8 < datasize) {
		uint32_t	size = dtoh32a(&curdata[PTP_ece_Size]);
		uint32_t	type = dtoh32a(&curdata[PTP_ece_Type]);

		if (size > datasize) {
			ptp_debug (params, "size %d is larger than datasize %d", size, datasize);
			break;
		}
		if (size < 8) {
			ptp_debug (params, "size %d is smaller than 8", size);
			break;
		}

		if ((size == 8) && (type == 0))
			break;

		if ((curdata - data) + size >= datasize) {
			ptp_debug (params, "canon eos event decoder ran over supplied data, skipping entries");
			break;
		}

		ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
		ce[i].u.info = NULL;
		switch (type) {
		case PTP_EC_CANON_EOS_ObjectAddedEx:
			if (size < PTP_ece_OA_Name+1) {
				ptp_debug (params, "size %d is smaller than %d", size, PTP_ece_OA_Name+1);
				break;
			}
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_OBJECTINFO;
			ce[i].u.object.oid    		= dtoh32a(&curdata[PTP_ece_OA_ObjectID]);
			ce[i].u.object.oi.StorageID	= dtoh32a(&curdata[PTP_ece_OA_StorageID]);
			ce[i].u.object.oi.ParentObject	= dtoh32a(&curdata[PTP_ece_OA_Parent]);
			ce[i].u.object.oi.ObjectFormat 	= dtoh16a(&curdata[PTP_ece_OA_OFC]);
			ce[i].u.object.oi.ObjectCompressedSize= dtoh32a(&curdata[PTP_ece_OA_Size]);
			ce[i].u.object.oi.Filename 	= strdup(((char*)&curdata[PTP_ece_OA_Name]));
			ptp_debug (params, "event %d: objectinfo added oid %08lx, parent %08lx, ofc %04x, size %d, filename %s", i, ce[i].u.object.oid, ce[i].u.object.oi.ParentObject, ce[i].u.object.oi.ObjectFormat, ce[i].u.object.oi.ObjectCompressedSize, ce[i].u.object.oi.Filename);
			break;
                case PTP_EC_CANON_EOS_ObjectAddedUnknown:
			if (size < PTP_ece2_OA_Name+1) {
				ptp_debug (params, "size %d is smaller than %d", size, PTP_ece2_OA_Name+1);
				break;
			}
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_OBJECTINFO;
			ce[i].u.object.oid    		= dtoh32a(&curdata[PTP_ece2_OA_ObjectID]);
			ce[i].u.object.oi.StorageID	= dtoh32a(&curdata[PTP_ece2_OA_StorageID]);
			ce[i].u.object.oi.ParentObject	= dtoh32a(&curdata[PTP_ece2_OA_Parent]);
			ce[i].u.object.oi.ObjectFormat 	= dtoh16a(&curdata[PTP_ece2_OA_OFC]);
			ce[i].u.object.oi.ObjectCompressedSize= dtoh32a(&curdata[PTP_ece2_OA_Size]);
			ce[i].u.object.oi.Filename 	= strdup(((char*)&curdata[PTP_ece2_OA_Name]));
			ptp_debug (params, "event %d: objectinfo added oid %08lx, parent %08lx, ofc %04x, size %d, filename %s", i, ce[i].u.object.oid, ce[i].u.object.oi.ParentObject, ce[i].u.object.oi.ObjectFormat, ce[i].u.object.oi.ObjectCompressedSize, ce[i].u.object.oi.Filename);
			break;
		case PTP_EC_CANON_EOS_RequestObjectTransfer:
		case PTP_EC_CANON_EOS_RequestObjectTransferNew:
			if (size < PTP_ece_OI_Name+1) {
				ptp_debug (params, "size %d is smaller than %d", size, PTP_ece_OI_Name+1);
				break;
			}
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_OBJECTTRANSFER;
			ce[i].u.object.oid    		= dtoh32a(&curdata[PTP_ece_OI_ObjectID]);
			ce[i].u.object.oi.StorageID 	= 0;
			ce[i].u.object.oi.ObjectFormat 	= dtoh16a(&curdata[PTP_ece_OI_OFC]);
			ce[i].u.object.oi.ParentObject	= 0;
			ce[i].u.object.oi.ObjectCompressedSize = dtoh32a(&curdata[PTP_ece_OI_Size]);
			ce[i].u.object.oi.Filename 	= strdup(((char*)&curdata[PTP_ece_OI_Name]));

			ptp_debug (params, "event %d: request object transfer oid %08lx, ofc %04x, size %d, filename %p", i, ce[i].u.object.oid, ce[i].u.object.oi.ObjectFormat, ce[i].u.object.oi.ObjectCompressedSize, ce[i].u.object.oi.Filename);
			break;
		case PTP_EC_CANON_EOS_AvailListChanged: {
			uint32_t	proptype = dtoh32a(&curdata[PTP_ece_Prop_Subtype]);
			uint32_t	propxtype = dtoh32a(&curdata[PTP_ece_Prop_Desc_Type]);
			uint32_t	propxcnt = dtoh32a(&curdata[PTP_ece_Prop_Desc_Count]);
			unsigned char	*xdata = &curdata[PTP_ece_Prop_Desc_Data];
			unsigned int	j;
			PTPDevicePropDesc	*dpd;

			if (size < PTP_ece_Prop_Desc_Data) {
				ptp_debug (params, "size %d is smaller than %d", size, PTP_ece_Prop_Desc_Data);
				break;
			}

			ptp_debug (params, "event %d: EOS prop %04x desc record, datasize %d, propxtype %d", i, proptype, size-PTP_ece_Prop_Desc_Data, propxtype);
			for (j=0;j<params->nrofcanon_props;j++)
				if (params->canon_props[j].proptype == proptype)
					break;
			if (j==params->nrofcanon_props) {
				ptp_debug (params, "event %d: propdesc %x, default value not found.", i, proptype);
				break;
			}
			dpd = &params->canon_props[j].dpd;


			if (propxtype != 3) {
				ptp_debug (params, "event %d: propxtype is %x for %04x, unhandled, size %d", i, propxtype, proptype, size);
				for (j=0;j<size-PTP_ece_Prop_Desc_Data;j++)
					ptp_debug (params, "    %d: %02x", j, xdata[j]);
				break;
			}
			if (! propxcnt)
				break;
			if (propxcnt >= 2<<16)
				break;

			ptp_debug (params, "event %d: propxtype is %x, prop is 0x%04x, data type is 0x%04x, propxcnt is %d.",
				   i, propxtype, proptype, dpd->DataType, propxcnt);
			dpd->FormFlag = PTP_DPFF_Enumeration;
			dpd->FORM.Enum.NumberOfValues = propxcnt;
			free (dpd->FORM.Enum.SupportedValue);
			dpd->FORM.Enum.SupportedValue = malloc (sizeof (PTPPropertyValue)*propxcnt);

			switch (proptype) {
			case PTP_DPC_CANON_EOS_ImageFormat:
			case PTP_DPC_CANON_EOS_ImageFormatCF:
			case PTP_DPC_CANON_EOS_ImageFormatSD:
			case PTP_DPC_CANON_EOS_ImageFormatExtHD:

				for (j=0;j<propxcnt;j++) {
					dpd->FORM.Enum.SupportedValue[j].u16 =
							ptp_unpack_EOS_ImageFormat( params, &xdata );
					ptp_debug (params, "event %d: suppval[%d] of %x is 0x%x.", i, j, proptype, dpd->FORM.Enum.SupportedValue[j].u16);
				}
				break;
			default:

				switch (dpd->DataType) {
#define XX( TYPE, CONV )\
					if (sizeof(dpd->FORM.Enum.SupportedValue[j].TYPE)*propxcnt + PTP_ece_Prop_Desc_Data > size) {	\
						ptp_debug (params, "size %d does not match needed %d", sizeof(dpd->FORM.Enum.SupportedValue[j].TYPE)*propxcnt + PTP_ece_Prop_Desc_Data, size);	\
						break;							\
					}								\
					for (j=0;j<propxcnt;j++) { 					\
						dpd->FORM.Enum.SupportedValue[j].TYPE = CONV(xdata); 	\
						ptp_debug (params, "event %d: suppval[%d] of %x is 0x%x.", i, j, proptype, CONV(xdata)); \
						xdata += 4;  \
					} \
					break;

				case PTP_DTC_INT16:	XX( i16, dtoh16a );
				case PTP_DTC_UINT32:	XX( u32, dtoh32a );
				case PTP_DTC_UINT16:	XX( u16, dtoh16a );
				case PTP_DTC_UINT8:	XX( u8,  dtoh8a );
#undef XX
				default:
					free (dpd->FORM.Enum.SupportedValue);
					dpd->FORM.Enum.SupportedValue = NULL;
					dpd->FORM.Enum.NumberOfValues = 0;
					ptp_debug (params ,"event %d: data type 0x%04x of %x unhandled, size %d, raw values:", i, dpd->DataType, proptype, dtoh32a(xdata), size);
					for (j=0;j<(size-PTP_ece_Prop_Desc_Data)/4;j++, xdata+=4)
						ptp_debug (params, "    %3d: 0x%8x", j, dtoh32a(xdata));
					break;
				}
			}
			break;
		}
		case PTP_EC_CANON_EOS_PropValueChanged:
			if (size >= 0xc) {
				unsigned int j;
				uint32_t	proptype = dtoh32a(&curdata[PTP_ece_Prop_Subtype]);
				unsigned char	*xdata = &curdata[PTP_ece_Prop_Val_Data];
				PTPDevicePropDesc	*dpd;

				if (size < PTP_ece_Prop_Val_Data) {
					ptp_debug (params, "size %d is smaller than %d", size, PTP_ece_Prop_Val_Data);
					break;
				}
				ptp_debug (params, "event %d: EOS prop %04x info record, datasize is %d", i, proptype, size-PTP_ece_Prop_Val_Data);
				for (j=0;j<params->nrofcanon_props;j++)
					if (params->canon_props[j].proptype == proptype)
						break;
				if (j<params->nrofcanon_props) {
					if (	(params->canon_props[j].size != size) ||
						(memcmp(params->canon_props[j].data,xdata,size-PTP_ece_Prop_Val_Data))) {
						params->canon_props[j].data = realloc(params->canon_props[j].data,size-PTP_ece_Prop_Val_Data);
						params->canon_props[j].size = size;
						memcpy (params->canon_props[j].data,xdata,size-PTP_ece_Prop_Val_Data);
					}
				} else {
					if (j)
						params->canon_props = realloc(params->canon_props, sizeof(params->canon_props[0])*(j+1));
					else
						params->canon_props = malloc(sizeof(params->canon_props[0]));
					params->canon_props[j].proptype = proptype;
					params->canon_props[j].size = size;
					params->canon_props[j].data = malloc(size-PTP_ece_Prop_Val_Data);
					memcpy(params->canon_props[j].data, xdata, size-PTP_ece_Prop_Val_Data);
					memset (&params->canon_props[j].dpd,0,sizeof(params->canon_props[j].dpd));
					params->canon_props[j].dpd.GetSet = 1;
					params->canon_props[j].dpd.FormFlag = PTP_DPFF_None;
					params->nrofcanon_props = j+1;
				}
				dpd = &params->canon_props[j].dpd;

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_PROPERTY;
				ce[i].u.propid = proptype;


				switch (proptype) {
#define XX(x) case PTP_DPC_CANON_##x:
					XX(EOS_FocusMode)
					XX(EOS_BatteryPower)
					XX(EOS_BatterySelect)
					XX(EOS_ModelID)
					XX(EOS_PTPExtensionVersion)
					XX(EOS_DPOFVersion)
					XX(EOS_AvailableShots)
					XX(EOS_CurrentStorage)
					XX(EOS_CurrentFolder)
					XX(EOS_MyMenu)
					XX(EOS_MyMenuList)
					XX(EOS_HDDirectoryStructure)
					XX(EOS_BatteryInfo)
					XX(EOS_AdapterInfo)
					XX(EOS_LensStatus)
					XX(EOS_CardExtension)
					XX(EOS_TempStatus)
					XX(EOS_ShutterCounter)
					XX(EOS_SerialNumber)
					XX(EOS_DepthOfFieldPreview)
					XX(EOS_EVFRecordStatus)
					XX(EOS_LvAfSystem)
					XX(EOS_FocusInfoEx)
					XX(EOS_DepthOfField)
					XX(EOS_Brightness)
					XX(EOS_EFComp)
					XX(EOS_LensName)
					XX(EOS_LensID)
#undef XX
						dpd->GetSet = PTP_DPGS_Get;
						break;
				}


				switch (proptype) {
				case PTP_DPC_CANON_EOS_CameraTime:
				case PTP_DPC_CANON_EOS_UTCTime:
				case PTP_DPC_CANON_EOS_Summertime:
				case PTP_DPC_CANON_EOS_AvailableShots:
				case PTP_DPC_CANON_EOS_CaptureDestination:
				case PTP_DPC_CANON_EOS_WhiteBalanceXA:
				case PTP_DPC_CANON_EOS_WhiteBalanceXB:
				case PTP_DPC_CANON_EOS_CurrentStorage:
				case PTP_DPC_CANON_EOS_CurrentFolder:
				case PTP_DPC_CANON_EOS_ShutterCounter:
				case PTP_DPC_CANON_EOS_ModelID:
				case PTP_DPC_CANON_EOS_LensID:
				case PTP_DPC_CANON_EOS_StroboFiring:
				case PTP_DPC_CANON_EOS_AFSelectFocusArea:
				case PTP_DPC_CANON_EOS_ContinousAFMode:
				case PTP_DPC_CANON_EOS_MirrorUpSetting:
					dpd->DataType = PTP_DTC_UINT32;
					break;

				case PTP_DPC_CANON_EOS_AutoExposureMode:
					dpd->DataType = PTP_DTC_UINT16;
					dpd->FormFlag = PTP_DPFF_Enumeration;
					dpd->FORM.Enum.NumberOfValues = 0;
					break;
				case PTP_DPC_CANON_EOS_Aperture:
				case PTP_DPC_CANON_EOS_ShutterSpeed:
				case PTP_DPC_CANON_EOS_ISOSpeed:
				case PTP_DPC_CANON_EOS_FocusMode:
				case PTP_DPC_CANON_EOS_ColorSpace:
				case PTP_DPC_CANON_EOS_BatteryPower:
				case PTP_DPC_CANON_EOS_BatterySelect:
				case PTP_DPC_CANON_EOS_PTPExtensionVersion:
				case PTP_DPC_CANON_EOS_DriveMode:
				case PTP_DPC_CANON_EOS_AEB:
				case PTP_DPC_CANON_EOS_BracketMode:
				case PTP_DPC_CANON_EOS_QuickReviewTime:
				case PTP_DPC_CANON_EOS_EVFMode:
				case PTP_DPC_CANON_EOS_EVFOutputDevice:
				case PTP_DPC_CANON_EOS_AutoPowerOff:
				case PTP_DPC_CANON_EOS_EVFRecordStatus:
					dpd->DataType = PTP_DTC_UINT16;
					break;
				case PTP_DPC_CANON_EOS_PictureStyle:
				case PTP_DPC_CANON_EOS_WhiteBalance:
				case PTP_DPC_CANON_EOS_MeteringMode:
				case PTP_DPC_CANON_EOS_ExpCompensation:
					dpd->DataType = PTP_DTC_UINT8;
					break;
				case PTP_DPC_CANON_EOS_Owner:
				case PTP_DPC_CANON_EOS_Artist:
				case PTP_DPC_CANON_EOS_Copyright:
				case PTP_DPC_CANON_EOS_SerialNumber:
				case PTP_DPC_CANON_EOS_LensName:
					dpd->DataType = PTP_DTC_STR;
					break;
				case PTP_DPC_CANON_EOS_WhiteBalanceAdjustA:
				case PTP_DPC_CANON_EOS_WhiteBalanceAdjustB:
					dpd->DataType = PTP_DTC_INT16;
					break;

				case PTP_DPC_CANON_EOS_DPOFVersion:
					dpd->DataType = PTP_DTC_UINT16;
					ptp_debug (params, "event %d: Unknown EOS property %04x, datasize is %d, using uint16", i ,proptype, size-PTP_ece_Prop_Val_Data);
					for (j=0;j<size-PTP_ece_Prop_Val_Data;j++)
						ptp_debug (params, "    %d: %02x", j, xdata[j]);
					break;
				case PTP_DPC_CANON_EOS_CustomFunc1:
				case PTP_DPC_CANON_EOS_CustomFunc2:
				case PTP_DPC_CANON_EOS_CustomFunc3:
				case PTP_DPC_CANON_EOS_CustomFunc4:
				case PTP_DPC_CANON_EOS_CustomFunc5:
				case PTP_DPC_CANON_EOS_CustomFunc6:
				case PTP_DPC_CANON_EOS_CustomFunc7:
				case PTP_DPC_CANON_EOS_CustomFunc8:
				case PTP_DPC_CANON_EOS_CustomFunc9:
				case PTP_DPC_CANON_EOS_CustomFunc10:
				case PTP_DPC_CANON_EOS_CustomFunc11:
					dpd->DataType = PTP_DTC_UINT8;
					ptp_debug (params, "event %d: Unknown EOS property %04x, datasize is %d, using uint8", i ,proptype, size-PTP_ece_Prop_Val_Data);
					for (j=0;j<size-PTP_ece_Prop_Val_Data;j++)
						ptp_debug (params, "    %d: %02x", j, xdata[j]);

					xdata += 4;
					break;

				case PTP_DPC_CANON_EOS_ColorTemperature:
				case PTP_DPC_CANON_EOS_WftStatus:
				case PTP_DPC_CANON_EOS_LensStatus:
				case PTP_DPC_CANON_EOS_CardExtension:
				case PTP_DPC_CANON_EOS_TempStatus:
				case PTP_DPC_CANON_EOS_PhotoStudioMode:
				case PTP_DPC_CANON_EOS_DepthOfFieldPreview:
				case PTP_DPC_CANON_EOS_EVFSharpness:
				case PTP_DPC_CANON_EOS_EVFWBMode:
				case PTP_DPC_CANON_EOS_EVFClickWBCoeffs:
				case PTP_DPC_CANON_EOS_EVFColorTemp:
				case PTP_DPC_CANON_EOS_ExposureSimMode:
				case PTP_DPC_CANON_EOS_LvAfSystem:
				case PTP_DPC_CANON_EOS_MovSize:
				case PTP_DPC_CANON_EOS_DepthOfField:
				case PTP_DPC_CANON_EOS_LvViewTypeSelect:
				case PTP_DPC_CANON_EOS_AloMode:
				case PTP_DPC_CANON_EOS_Brightness:
					dpd->DataType = PTP_DTC_UINT32;
					ptp_debug (params, "event %d: Unknown EOS property %04x, datasize is %d, using uint32", i ,proptype, size-PTP_ece_Prop_Val_Data);
					if ((size-PTP_ece_Prop_Val_Data) % sizeof(uint32_t) != 0)
						ptp_debug (params, "event %d: Warning: datasize modulo sizeof(uint32) is not 0: ", i, (size-PTP_ece_Prop_Val_Data) % sizeof(uint32_t) );
					for (j=0;j<(size-PTP_ece_Prop_Val_Data)/sizeof(uint32_t);j++)
						ptp_debug (params, "    %d: 0x%8x", j, dtoh32a(xdata+j*4));
					break;

				case PTP_DPC_CANON_EOS_ImageFormat:
				case PTP_DPC_CANON_EOS_ImageFormatCF:
				case PTP_DPC_CANON_EOS_ImageFormatSD:
				case PTP_DPC_CANON_EOS_ImageFormatExtHD:
				case PTP_DPC_CANON_EOS_CustomFuncEx:
				case PTP_DPC_CANON_EOS_FocusInfoEx:
					break;
				default:
					ptp_debug (params, "event %d: Unknown EOS property %04x, datasize is %d", i ,proptype, size-PTP_ece_Prop_Val_Data);
					for (j=0;j<size-PTP_ece_Prop_Val_Data;j++)
						ptp_debug (params, "    %d: %02x", j, xdata[j]);
					break;
				}
				switch (dpd->DataType) {
				case PTP_DTC_UINT32:
					dpd->FactoryDefaultValue.u32	= dtoh32a(xdata);
					dpd->CurrentValue.u32		= dtoh32a(xdata);
					ptp_debug (params ,"event %d: currentvalue of %x is %x", i, proptype, dpd->CurrentValue.u32);
					break;
				case PTP_DTC_INT16:
					dpd->FactoryDefaultValue.i16	= dtoh16a(xdata);
					dpd->CurrentValue.i16		= dtoh16a(xdata);
					ptp_debug (params,"event %d: currentvalue of %x is %d", i, proptype, dpd->CurrentValue.i16);
					break;
				case PTP_DTC_UINT16:
					dpd->FactoryDefaultValue.u16	= dtoh16a(xdata);
					dpd->CurrentValue.u16		= dtoh16a(xdata);
					ptp_debug (params,"event %d: currentvalue of %x is %x", i, proptype, dpd->CurrentValue.u16);
					break;
				case PTP_DTC_UINT8:
					dpd->FactoryDefaultValue.u8	= dtoh8a(xdata);
					dpd->CurrentValue.u8		= dtoh8a(xdata);
					ptp_debug (params,"event %d: currentvalue of %x is %x", i, proptype, dpd->CurrentValue.u8);
					break;
				case PTP_DTC_INT8:
					dpd->FactoryDefaultValue.i8	= dtoh8a(xdata);
					dpd->CurrentValue.i8		= dtoh8a(xdata);
					ptp_debug (params,"event %d: currentvalue of %x is %x", i, proptype, dpd->CurrentValue.i8);
					break;
				case PTP_DTC_STR: {
#if 0
					uint8_t len = 0;
					dpd->FactoryDefaultValue.str	= ptp_unpack_string(params, data, 0, &len);
					dpd->CurrentValue.str		= ptp_unpack_string(params, data, 0, &len);
#else
					free (dpd->FactoryDefaultValue.str);
					dpd->FactoryDefaultValue.str	= strdup( (char*)xdata );

					free (dpd->CurrentValue.str);
					dpd->CurrentValue.str		= strdup( (char*)xdata );
#endif
					ptp_debug (params,"event %d: currentvalue of %x is %s", i, proptype, dpd->CurrentValue.str);
					break;
				}
				default:

					break;
				}


				switch (proptype) {
				case PTP_DPC_CANON_EOS_ImageFormat:
				case PTP_DPC_CANON_EOS_ImageFormatCF:
				case PTP_DPC_CANON_EOS_ImageFormatSD:
				case PTP_DPC_CANON_EOS_ImageFormatExtHD:
					dpd->DataType = PTP_DTC_UINT16;
					dpd->FactoryDefaultValue.u16	= ptp_unpack_EOS_ImageFormat( params, &xdata );
					dpd->CurrentValue.u16		= dpd->FactoryDefaultValue.u16;
					ptp_debug (params,"event %d: decoded imageformat, currentvalue of %x is %x", i, proptype, dpd->CurrentValue.u16);
					break;
				case PTP_DPC_CANON_EOS_CustomFuncEx:
					dpd->DataType = PTP_DTC_STR;
					free (dpd->FactoryDefaultValue.str);
					free (dpd->CurrentValue.str);
					dpd->FactoryDefaultValue.str	= ptp_unpack_EOS_CustomFuncEx( params, &xdata );
					dpd->CurrentValue.str		= strdup( (char*)dpd->FactoryDefaultValue.str );
					ptp_debug (params,"event %d: decoded custom function, currentvalue of %x is %s", i, proptype, dpd->CurrentValue.str);
					break;
				case PTP_DPC_CANON_EOS_FocusInfoEx:
					dpd->DataType = PTP_DTC_STR;
					free (dpd->FactoryDefaultValue.str);
					free (dpd->CurrentValue.str);
					dpd->FactoryDefaultValue.str	= ptp_unpack_EOS_FocusInfoEx( params, &xdata, size );
					dpd->CurrentValue.str		= strdup( (char*)dpd->FactoryDefaultValue.str );
					ptp_debug (params,"event %d: decoded focus info, currentvalue of %x is %s", i, proptype, dpd->CurrentValue.str);
					break;
				}

				break;
		}

		case PTP_EC_CANON_EOS_OLCInfoChanged: {
			uint32_t		len, curoff;
			uint16_t		mask,proptype;
			PTPDevicePropDesc	*dpd;


			ptp_debug (params, "event %d: EOS event OLCInfoChanged (size %d)", i, size);
			if (size >= 0x8) {
				unsigned int k;
				for (k=8;k<size;k++)
					ptp_debug (params, "    %d: %02x", k-8, curdata[k]);
			}
			len = dtoh32a(curdata+8);
			if ((len != size-8) && (len != size-4)) {
				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = strdup("OLC size unexpected");
				ptp_debug (params, "event %d: OLC unexpected size %d for blob len %d (not -4 nor -8)", i, size, len);
				break;
			}
			mask = dtoh16a(curdata+8+4);
			if (size < 14) {
				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = strdup("OLC size too small");
				ptp_debug (params, "event %d: OLC unexpected size %d", i, size);
				break;
			}
			curoff = 8+4+4;
			if (mask & CANON_EOS_OLC_BUTTON) {
				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("Button 1234567"));
				sprintf(ce[i].u.info, "Button %d",  dtoh16a(curdata+curoff));
				i++;
				curoff += 2;
			}

			if (mask & CANON_EOS_OLC_SHUTTERSPEED) {


				proptype = PTP_DPC_CANON_EOS_ShutterSpeed;
				dpd = _lookup_or_allocate_canon_prop(params, proptype);
				dpd->CurrentValue.u16 = curdata[curoff+5];

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_PROPERTY;
				ce[i].u.propid = proptype;
				curoff += 6;
				i++;
			}
			if (mask & CANON_EOS_OLC_APERTURE) {


				proptype = PTP_DPC_CANON_EOS_Aperture;
				dpd = _lookup_or_allocate_canon_prop(params, proptype);
				dpd->CurrentValue.u16 = curdata[curoff+4];

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_PROPERTY;
				ce[i].u.propid = proptype;
				curoff += 5;
				i++;
			}
			if (mask & CANON_EOS_OLC_ISO) {


				proptype = PTP_DPC_CANON_EOS_ISOSpeed;
				dpd = _lookup_or_allocate_canon_prop(params, proptype);
				dpd->CurrentValue.u16 = curdata[curoff+3];

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_PROPERTY;
				ce[i].u.propid = proptype;
				curoff += 4;
				i++;
			}
			if (mask & 0x0010) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x0010 content 01234567")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x0010 content %02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3]
				);
				curoff += 4;
				i++;
			}
			if (mask & 0x0020) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x0020 content 0123456789ab")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x0020 content %02x%02x%02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5]
				);
				curoff += 6;
				i++;
			}
			if (mask & 0x0040) {
				int	value = (signed char)curdata[curoff+2];


				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo exposure indicator 012345678901234567890123456789abcd")+1);
				sprintf(ce[i].u.info,"OLCInfo exposure indicator %d,%d,%d.%d (%02x%02x%02x%02x)",
					curdata[curoff],
					curdata[curoff+1],
					value/10,abs(value)%10,
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5],
					curdata[curoff+6]
				);
				curoff += 7;
				i++;
			}
			if (mask & 0x0080) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x0080 content 01234567")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x0080 content %02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3]
				);
				curoff += 4;
				i++;
			}
			if (mask & 0x0100) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_FOCUSINFO;
				ce[i].u.info = malloc(strlen("0123456789ab")+1);
				sprintf(ce[i].u.info,"%02x%02x%02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5]
				);
				curoff += 6;
				i++;
			}
			if (mask & 0x0200) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_FOCUSMASK;
				ce[i].u.info = malloc(strlen("0123456789abcd0123456789abcdef")+1);
				sprintf(ce[i].u.info,"%02x%02x%02x%02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5],
					curdata[curoff+6]
				);
				curoff += 7;
				i++;
			}
			if (mask & 0x0400) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x0400 content 0123456789abcd")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x0400 content %02x%02x%02x%02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5],
					curdata[curoff+6]
				);
				curoff += 7;
				i++;
			}
			if (mask & 0x0800) {


				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x0800 content 0123456789abcdef")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x0800 content %02x%02x%02x%02x%02x%02x%02x%02x",
					curdata[curoff],
					curdata[curoff+1],
					curdata[curoff+2],
					curdata[curoff+3],
					curdata[curoff+4],
					curdata[curoff+5],
					curdata[curoff+6],
					curdata[curoff+7]
				);
				curoff += 8;
				i++;
			}
			if (mask & 0x1000) {

				ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
				ce[i].u.info = malloc(strlen("OLCInfo event 0x1000 content 01")+1);
				sprintf(ce[i].u.info,"OLCInfo event 0x1000 content %02x",
					curdata[curoff]
				);
				curoff += 1;
				i++;
			}

			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
			ce[i].u.info = malloc(strlen("OLCInfo event mask 0123456789")+1);
			sprintf(ce[i].u.info, "OLCInfo event mask=%x",  mask);
			break;
		}
		case PTP_EC_CANON_EOS_CameraStatusChanged:
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_CAMERASTATUS;
			ce[i].u.status =  dtoh32a(curdata+8);
			ptp_debug (params, "event %d: EOS event CameraStatusChanged (size %d) = %d", i, size, dtoh32a(curdata+8));
			params->eos_camerastatus = dtoh32a(curdata+8);
			break;
		case 0:
			if (size == 8)
				break;
			ptp_debug (params, "event %d: EOS event 0, but size %d", i, size);
			break;
		case PTP_EC_CANON_EOS_BulbExposureTime:
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
			ce[i].u.info = malloc(strlen("BulbExposureTime 123456789012345678"));
			sprintf (ce[i].u.info, "BulbExposureTime %d",  dtoh32a(curdata+8));
			break;
		case PTP_EC_CANON_EOS_ObjectRemoved:
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_OBJECTREMOVED;
			ce[i].u.object.oid = dtoh32a(curdata+8);
			break;
		default:
			switch (type) {
#define XX(x)		case PTP_EC_CANON_EOS_##x: 								\
				ptp_debug (params, "event %d: unhandled EOS event "#x" (size %d)", i, size); 	\
				ce[i].u.info = malloc(strlen("unhandled EOS event "#x" (size 123456789)"));	\
				sprintf (ce[i].u.info, "unhandled EOS event "#x" (size %d)",  size);		\
				break;
			XX(RequestGetEvent)
			XX(RequestGetObjectInfoEx)
			XX(StorageStatusChanged)
			XX(StorageInfoChanged)
			XX(ObjectInfoChangedEx)
			XX(ObjectContentChanged)
			XX(WillSoonShutdown)
			XX(ShutdownTimerUpdated)
			XX(RequestCancelTransfer)
			XX(RequestObjectTransferDT)
			XX(RequestCancelTransferDT)
			XX(StoreAdded)
			XX(StoreRemoved)
			XX(BulbExposureTime)
			XX(RecordingTime)
			XX(RequestObjectTransferTS)
			XX(AfResult)
#undef XX
			default:
				ptp_debug (params, "event %d: unknown EOS event %04x", i, type);
				break;
			}
			if (size >= 0x8) {
				unsigned int j;

				for (j=8;j<size;j++)
					ptp_debug (params, "    %d: %02x", j, curdata[j]);
			}
			ce[i].type = PTP_CANON_EOS_CHANGES_TYPE_UNKNOWN;
			break;
		}
		curdata += size;
		i++;
		if (i >= entries) {
			ptp_debug (params, "BAD: i %d, entries %d", i, entries);
		}
	}
	if (!i) {
		free (ce);
		ce = NULL;
	}
	*pce = ce;
	return i;
}
