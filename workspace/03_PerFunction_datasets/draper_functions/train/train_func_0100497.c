s_TellSaveFailed(XAP_Frame * pFrame, const char * fileName, UT_Error errorCode)
{
	XAP_String_Id String_id;

    switch(errorCode) {
    case UT_SAVE_CANCELLED:
        return;

    case UT_SAVE_WRITEERROR:
        String_id = AP_STRING_ID_MSG_SaveFailedWrite;
        break;

	case UT_SAVE_NAMEERROR:
        String_id = AP_STRING_ID_MSG_SaveFailedName;
        break;

	case UT_SAVE_EXPORTERROR:
        String_id = AP_STRING_ID_MSG_SaveFailedExport;
        break;

	default:
        String_id = AP_STRING_ID_MSG_SaveFailed;
        break;
    }
	pFrame->showMessageBox(String_id,
			       XAP_Dialog_MessageBox::b_O,
			       XAP_Dialog_MessageBox::a_OK,
			       fileName);
}
