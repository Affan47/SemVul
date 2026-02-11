vAddStartTag(diagram_type *pDiag, UCHAR ucTag, const char *szAttribute)
{
	fail(pDiag == NULL);
	fail(pDiag->pOutFile == NULL);
	fail((size_t)ucTag >= elementsof(atDocBookTags));

	if (atDocBookTags[(UINT)ucTag].bAddNewlineStart) {
		fprintf(pDiag->pOutFile, "\n");
		vPrintLevel(pDiag->pOutFile);
	}

	if (szAttribute == NULL || szAttribute[0] == '\0') {
		fprintf(pDiag->pOutFile, "<%s>",
			atDocBookTags[(UINT)ucTag].szTagname);
	} else {
		fprintf(pDiag->pOutFile, "<%s %s>",
			atDocBookTags[(UINT)ucTag].szTagname, szAttribute);
	}

	if (atDocBookTags[(UINT)ucTag].bAddNewlineEnd) {
		fprintf(pDiag->pOutFile, "\n");
		pDiag->lXleft = 0;
	}

	vPushStack(ucTag);


	switch (ucTag) {
	case TAG_CHAPTER:
		usHeaderLevelCurrent = 1;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_SECT1:
		usHeaderLevelCurrent = 2;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_SECT2:
		usHeaderLevelCurrent = 3;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_SECT3:
		usHeaderLevelCurrent = 4;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_SECT4:
		usHeaderLevelCurrent = 5;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_SECT5:
		usHeaderLevelCurrent = 6;
		bEmptyHeaderLevel = TRUE;
		break;
	case TAG_TITLE:
		fail(uiParagraphLevel != 0);
		bTitleOpen = TRUE;
		break;
	case TAG_FOOTNOTE:
		bFootnoteOpen = TRUE;
		break;
	case TAG_PARA:
		fail(bTitleOpen && !bFootnoteOpen);
		uiParagraphLevel++;
		bEmptyHeaderLevel = FALSE;
		break;
	case TAG_EMPHASIS:
		bEmphasisOpen = TRUE;
		break;
	case TAG_ITEMIZEDLIST:
	case TAG_ORDEREDLIST:
		uiListLevel++;
		bEmptyListLevel = TRUE;
		bEmptyHeaderLevel = FALSE;
		break;
	case TAG_LISTITEM:
		bEmptyListLevel = FALSE;
		break;
	case TAG_SUPERSCRIPT:
		bSuperscriptOpen = TRUE;
		break;
	case TAG_SUBSCRIPT:
		bSubscriptOpen = TRUE;
		break;
	case TAG_INFORMALTABLE:
		bTableOpen = TRUE;
		bEmptyHeaderLevel = FALSE;
		break;
	default:
		break;
	}
}
