uchar *MsgGetProp(msg_t *pMsg, struct templateEntry *pTpe,
                 propid_t propID, size_t *pPropLen,
		 unsigned short *pbMustBeFreed)
{
	uchar *pRes;
	int bufLen = -1;
	uchar *pBufStart;
	uchar *pBuf;
	int iLen;
	short iOffs;

	BEGINfunc
	assert(pMsg != NULL);
	assert(pbMustBeFreed != NULL);

#ifdef	FEATURE_REGEXP

	size_t nmatch = 10;
	regmatch_t pmatch[10];
#endif

	*pbMustBeFreed = 0;

	switch(propID) {
		case PROP_MSG:
			pRes = getMSG(pMsg);
			bufLen = getMSGLen(pMsg);
			break;
		case PROP_TIMESTAMP:
			pRes = (uchar*)getTimeReported(pMsg, pTpe->data.field.eDateFormat);
			break;
		case PROP_HOSTNAME:
			pRes = (uchar*)getHOSTNAME(pMsg);
			bufLen = getHOSTNAMELen(pMsg);
			break;
		case PROP_SYSLOGTAG:
			getTAG(pMsg, &pRes, &bufLen);
			break;
		case PROP_RAWMSG:
			getRawMsg(pMsg, &pRes, &bufLen);
			break;


		case PROP_INPUTNAME:
			getInputName(pMsg, &pRes, &bufLen);
			break;
		case PROP_FROMHOST:
			pRes = getRcvFrom(pMsg);
			break;
		case PROP_FROMHOST_IP:
			pRes = getRcvFromIP(pMsg);
			break;
		case PROP_PRI:
			pRes = (uchar*)getPRI(pMsg);
			break;
		case PROP_PRI_TEXT:
			pBuf = MALLOC(20 * sizeof(uchar));
			if(pBuf == NULL) {
				RET_OUT_OF_MEMORY;
			} else {
				*pbMustBeFreed = 1;
				pRes = (uchar*)textpri((char*)pBuf, 20, getPRIi(pMsg));
			}
			break;
		case PROP_IUT:
			pRes = UCHAR_CONSTANT("1");
			bufLen = 1;
			break;
		case PROP_SYSLOGFACILITY:
			pRes = (uchar*)getFacility(pMsg);
			break;
		case PROP_SYSLOGFACILITY_TEXT:
			pRes = (uchar*)getFacilityStr(pMsg);
			break;
		case PROP_SYSLOGSEVERITY:
			pRes = (uchar*)getSeverity(pMsg);
			break;
		case PROP_SYSLOGSEVERITY_TEXT:
			pRes = (uchar*)getSeverityStr(pMsg);
			break;
		case PROP_TIMEGENERATED:
			pRes = (uchar*)getTimeGenerated(pMsg, pTpe->data.field.eDateFormat);
			break;
		case PROP_PROGRAMNAME:
			pRes = getProgramName(pMsg, LOCK_MUTEX);
			break;
		case PROP_PROTOCOL_VERSION:
			pRes = (uchar*)getProtocolVersionString(pMsg);
			break;
		case PROP_STRUCTURED_DATA:
			pRes = (uchar*)getStructuredData(pMsg);
			break;
		case PROP_APP_NAME:
			pRes = (uchar*)getAPPNAME(pMsg, LOCK_MUTEX);
			break;
		case PROP_PROCID:
			pRes = (uchar*)getPROCID(pMsg, LOCK_MUTEX);
			break;
		case PROP_MSGID:
			pRes = (uchar*)getMSGID(pMsg);
			break;
		case PROP_SYS_NOW:
			if((pRes = getNOW(NOW_NOW)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_YEAR:
			if((pRes = getNOW(NOW_YEAR)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_MONTH:
			if((pRes = getNOW(NOW_MONTH)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_DAY:
			if((pRes = getNOW(NOW_DAY)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_HOUR:
			if((pRes = getNOW(NOW_HOUR)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_HHOUR:
			if((pRes = getNOW(NOW_HHOUR)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_QHOUR:
			if((pRes = getNOW(NOW_QHOUR)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_MINUTE:
			if((pRes = getNOW(NOW_MINUTE)) == NULL) {
				RET_OUT_OF_MEMORY;
			} else
				*pbMustBeFreed = 1;
			break;
		case PROP_SYS_MYHOSTNAME:
			pRes = glbl.GetLocalHostName();
			break;
		default:


			dbgprintf("invalid property id: '%d'\n", propID);
			*pbMustBeFreed = 0;
			*pPropLen = sizeof("**INVALID PROPERTY NAME**") - 1;
			return UCHAR_CONSTANT("**INVALID PROPERTY NAME**");
	}


	if(pTpe == NULL) {
		return pRes;
	}


	if(pTpe->data.field.has_fields == 1) {
		size_t iCurrFld;
		uchar *pFld;
		uchar *pFldEnd;


		iCurrFld = 1;
		pFld = pRes;
		while(*pFld && iCurrFld < pTpe->data.field.iToPos) {

			while(*pFld && (uchar) *pFld != pTpe->data.field.field_delim)
				++pFld;
			if(*pFld == pTpe->data.field.field_delim) {
				++pFld;
				if (pTpe->data.field.field_expand != 0) {
					while (*pFld == pTpe->data.field.field_delim) {
						++pFld;
					}
				}
				++iCurrFld;
			}
		}
		dbgprintf("field requested %d, field found %d\n", pTpe->data.field.iToPos, (int) iCurrFld);

		if(iCurrFld == pTpe->data.field.iToPos) {


			pFldEnd = pFld;
			while(*pFldEnd && *pFldEnd != pTpe->data.field.field_delim)
				++pFldEnd;
			--pFldEnd;


			iLen = pFldEnd - pFld + 1;
			pBufStart = pBuf = MALLOC((iLen + 1) * sizeof(char));
			if(pBuf == NULL) {
				if(*pbMustBeFreed == 1)
					free(pRes);
				RET_OUT_OF_MEMORY;
			}

			memcpy(pBuf, pFld, iLen);
			bufLen = iLen;
			pBuf[iLen] = '\0';
			if(*pbMustBeFreed == 1)
				free(pRes);
			pRes = pBufStart;
			*pbMustBeFreed = 1;
			if(*(pFldEnd+1) != '\0')
				++pFldEnd;
		} else {

			if(*pbMustBeFreed == 1)
				free(pRes);
			*pbMustBeFreed = 0;
			*pPropLen = sizeof("**FIELD NOT FOUND**") - 1;
			return UCHAR_CONSTANT("**FIELD NOT FOUND**");
		}
	} else if(pTpe->data.field.iFromPos != 0 || pTpe->data.field.iToPos != 0) {

		int iFrom, iTo;
		uchar *pSb;
		iFrom = pTpe->data.field.iFromPos;
		iTo = pTpe->data.field.iToPos;

		if(iFrom > 0)
			--iFrom;
		if(iTo > 0)
			--iTo;
		if(bufLen == -1)
			bufLen = ustrlen(pRes);
		if(iFrom == 0 && iTo >=  bufLen) {


			;
		} else {
			iLen = iTo - iFrom + 1;
			pBufStart = pBuf = MALLOC((iLen + 1) * sizeof(char));
			if(pBuf == NULL) {
				if(*pbMustBeFreed == 1)
					free(pRes);
				RET_OUT_OF_MEMORY;
			}
			pSb = pRes;
			if(iFrom) {


				while(*pSb && iFrom) {
					--iFrom;
					++pSb;
				}
			}

			bufLen = iLen;
			while(*pSb && iLen) {
				*pBuf++ = *pSb;
				++pSb;
				--iLen;
			}
			*pBuf = '\0';
			bufLen -= iLen;
			if(*pbMustBeFreed == 1)
				free(pRes);
			pRes = pBufStart;
			*pbMustBeFreed = 1;
		}
#ifdef FEATURE_REGEXP
	} else {

		if (pTpe->data.field.has_regex != 0) {
			if (pTpe->data.field.has_regex == 2) {

				if (*pbMustBeFreed == 1) {
					free(pRes);
					*pbMustBeFreed = 0;
				}
				*pPropLen = sizeof("**NO MATCH** **BAD REGULAR EXPRESSION**") - 1;
				return UCHAR_CONSTANT("**NO MATCH** **BAD REGULAR EXPRESSION**");
			}

			dbgprintf("string to match for regex is: %s\n", pRes);

			if(objUse(regexp, LM_REGEXP_FILENAME) == RS_RET_OK) {
				short iTry = 0;
				uchar bFound = 0;
				iOffs = 0;


				while(!bFound) {
					int iREstat;
					iREstat = regexp.regexec(&pTpe->data.field.re, (char*)(pRes + iOffs), nmatch, pmatch, 0);
					dbgprintf("regexec return is %d\n", iREstat);
					if(iREstat == 0) {
						if(pmatch[0].rm_so == -1) {
							dbgprintf("oops ... start offset of successful regexec is -1\n");
							break;
						}
						if(iTry == pTpe->data.field.iMatchToUse) {
							bFound = 1;
						} else {
							dbgprintf("regex found at offset %d, new offset %d, tries %d\n",
								  iOffs, (int) (iOffs + pmatch[0].rm_eo), iTry);
							iOffs += pmatch[0].rm_eo;
							++iTry;
						}
					} else {
						break;
					}
				}
				dbgprintf("regex: end search, found %d\n", bFound);
				if(!bFound) {

					if(pTpe->data.field.nomatchAction != TPL_REGEX_NOMATCH_USE_WHOLE_FIELD) {
						if (*pbMustBeFreed == 1) {
							free(pRes);
							*pbMustBeFreed = 0;
						}
						if(pTpe->data.field.nomatchAction == TPL_REGEX_NOMATCH_USE_DFLTSTR) {
							bufLen = sizeof("**NO MATCH**") - 1;
							pRes = UCHAR_CONSTANT("**NO MATCH**");
						} else if(pTpe->data.field.nomatchAction == TPL_REGEX_NOMATCH_USE_ZERO) {
							bufLen = 1;
							pRes = UCHAR_CONSTANT("0");
						} else {
							bufLen = 0;
							pRes = UCHAR_CONSTANT("");
						}
					}
				} else {


					if(pmatch[pTpe->data.field.iSubMatchToUse].rm_so == -1) {
						if(pTpe->data.field.nomatchAction != TPL_REGEX_NOMATCH_USE_WHOLE_FIELD) {
							if (*pbMustBeFreed == 1) {
								free(pRes);
								*pbMustBeFreed = 0;
							}
							if(pTpe->data.field.nomatchAction == TPL_REGEX_NOMATCH_USE_DFLTSTR) {
								bufLen = sizeof("**NO MATCH**") - 1;
								pRes = UCHAR_CONSTANT("**NO MATCH**");
							} else if(pTpe->data.field.nomatchAction == TPL_REGEX_NOMATCH_USE_ZERO) {
								bufLen = 1;
								pRes = UCHAR_CONSTANT("0");
							} else {
								bufLen = 0;
								pRes = UCHAR_CONSTANT("");
							}
						}
					}

					int iLenBuf;
					uchar *pB;

					iLenBuf = pmatch[pTpe->data.field.iSubMatchToUse].rm_eo
						  - pmatch[pTpe->data.field.iSubMatchToUse].rm_so;
					pB = MALLOC((iLenBuf + 1) * sizeof(uchar));

					if (pB == NULL) {
						if (*pbMustBeFreed == 1)
							free(pRes);
						RET_OUT_OF_MEMORY;
					}


					memcpy(pB, pRes + iOffs +  pmatch[pTpe->data.field.iSubMatchToUse].rm_so, iLenBuf);
					bufLen = iLenBuf;
					pB[iLenBuf] = '\0';

					if (*pbMustBeFreed == 1)
						free(pRes);
					pRes = pB;
					*pbMustBeFreed = 1;
				}
			} else {


				dbgprintf("could not get regexp object pointer, so regexp can not be evaluated\n");
				if (*pbMustBeFreed == 1) {
					free(pRes);
					*pbMustBeFreed = 0;
				}
				*pPropLen = sizeof("***REGEXP NOT AVAILABLE***") - 1;
				return UCHAR_CONSTANT("***REGEXP NOT AVAILABLE***");
			}
		}
#endif
	}


	if(*pRes && pTpe->data.field.options.bSPIffNo1stSP) {

		uchar cFirst = *pRes;
		if(*pbMustBeFreed == 1)
			free(pRes);
		pRes = (cFirst == ' ') ? UCHAR_CONSTANT("") : UCHAR_CONSTANT(" ");
		bufLen = (cFirst == ' ') ? 0 : 1;
		*pbMustBeFreed = 0;
	}

	if(*pRes) {


		if(pTpe->data.field.eCaseConv != tplCaseConvNo) {

			if(bufLen == -1)
				bufLen = ustrlen(pRes);
			uchar *pBStart;
			uchar *pB;
			uchar *pSrc;
			pBStart = pB = MALLOC((bufLen + 1) * sizeof(char));
			if(pB == NULL) {
				if(*pbMustBeFreed == 1)
					free(pRes);
				RET_OUT_OF_MEMORY;
			}
			pSrc = pRes;
			while(*pSrc) {
				*pB++ = (pTpe->data.field.eCaseConv == tplCaseConvUpper) ?
					(uchar)toupper((int)*pSrc) : (uchar)tolower((int)*pSrc);

				++pSrc;
			}
			*pB = '\0';
			if(*pbMustBeFreed == 1)
				free(pRes);
			pRes = pBStart;
			*pbMustBeFreed = 1;
		}


		if(pTpe->data.field.options.bDropCC) {
			int iLenBuf = 0;
			uchar *pSrc = pRes;
			uchar *pDstStart;
			uchar *pDst;
			uchar bDropped = 0;

			while(*pSrc) {
				if(!iscntrl((int) *pSrc++))
					iLenBuf++;
				else
					bDropped = 1;
			}

			if(bDropped) {
				pDst = pDstStart = MALLOC(iLenBuf + 1);
				if(pDst == NULL) {
					if(*pbMustBeFreed == 1)
						free(pRes);
					RET_OUT_OF_MEMORY;
				}
				for(pSrc = pRes; *pSrc; pSrc++) {
					if(!iscntrl((int) *pSrc))
						*pDst++ = *pSrc;
				}
				*pDst = '\0';
				if(*pbMustBeFreed == 1)
					free(pRes);
				pRes = pDstStart;
				bufLen = iLenBuf;
				*pbMustBeFreed = 1;
			}
		} else if(pTpe->data.field.options.bSpaceCC) {
			uchar *pSrc;
			uchar *pDstStart;
			uchar *pDst;

			if(*pbMustBeFreed == 1) {


				for(pDst = pRes; *pDst; pDst++) {
					if(iscntrl((int) *pDst))
						*pDst = ' ';
				}
			} else {
				if(bufLen == -1)
					bufLen = ustrlen(pRes);
				pDst = pDstStart = MALLOC(bufLen + 1);
				if(pDst == NULL) {
					if(*pbMustBeFreed == 1)
						free(pRes);
					RET_OUT_OF_MEMORY;
				}
				for(pSrc = pRes; *pSrc; pSrc++) {
					if(iscntrl((int) *pSrc))
						*pDst++ = ' ';
					else
						*pDst++ = *pSrc;
				}
				*pDst = '\0';
				pRes = pDstStart;
				*pbMustBeFreed = 1;
			}
		} else if(pTpe->data.field.options.bEscapeCC) {


			int iNumCC = 0;
			int iLenBuf = 0;
			uchar *pB;

			for(pB = pRes ; *pB ; ++pB) {
				++iLenBuf;
				if(iscntrl((int) *pB))
					++iNumCC;
			}

			if(iNumCC > 0) {

				uchar *pBStart;
				uchar szCCEsc[8];
				int i;

				iLenBuf += iNumCC * 4;
				pBStart = pB = MALLOC((iLenBuf + 1) * sizeof(uchar));
				if(pB == NULL) {
					if(*pbMustBeFreed == 1)
						free(pRes);
					RET_OUT_OF_MEMORY;
				}
				while(*pRes) {
					if(iscntrl((int) *pRes)) {
						snprintf((char*)szCCEsc, sizeof(szCCEsc), "#%3.3d", *pRes);
						for(i = 0 ; i < 4 ; ++i)
							*pB++ = szCCEsc[i];
					} else {
						*pB++ = *pRes;
					}
					++pRes;
				}
				*pB = '\0';
				if(*pbMustBeFreed == 1)
					free(pRes);
				pRes = pBStart;
				bufLen = -1;
				*pbMustBeFreed = 1;
			}
		}
	}


	if(pTpe->data.field.options.bSecPathDrop || pTpe->data.field.options.bSecPathReplace) {
		if(pTpe->data.field.options.bSecPathDrop) {
			int iLenBuf = 0;
			uchar *pSrc = pRes;
			uchar *pDstStart;
			uchar *pDst;
			uchar bDropped = 0;

			while(*pSrc) {
				if(*pSrc++ != '/')
					iLenBuf++;
				else
					bDropped = 1;
			}

			if(bDropped) {
				pDst = pDstStart = MALLOC(iLenBuf + 1);
				if(pDst == NULL) {
					if(*pbMustBeFreed == 1)
						free(pRes);
					RET_OUT_OF_MEMORY;
				}
				for(pSrc = pRes; *pSrc; pSrc++) {
					if(*pSrc != '/')
						*pDst++ = *pSrc;
				}
				*pDst = '\0';
				if(*pbMustBeFreed == 1)
					free(pRes);
				pRes = pDstStart;
				bufLen = -1;
				*pbMustBeFreed = 1;
			}
		} else {
			uchar *pSrc;
			uchar *pDstStart;
			uchar *pDst;

			if(*pbMustBeFreed == 1) {


				for(pDst = pRes; *pDst; pDst++) {
					if(*pDst == '/')
						*pDst++ = '_';
				}
			} else {
				if(bufLen == -1)
					bufLen = ustrlen(pRes);
				pDst = pDstStart = MALLOC(bufLen + 1);
				if(pDst == NULL) {
					if(*pbMustBeFreed == 1)
						free(pRes);
					RET_OUT_OF_MEMORY;
				}
				for(pSrc = pRes; *pSrc; pSrc++) {
					if(*pSrc == '/')
						*pDst++ = '_';
					else
						*pDst++ = *pSrc;
				}
				*pDst = '\0';


				pRes = pDstStart;
				*pbMustBeFreed = 1;
			}
		}


		if((*pRes == '.') && (*(pRes + 1) == '\0' || (*(pRes + 1) == '.' && *(pRes + 2) == '\0'))) {
			uchar *pTmp = pRes;

			if(*(pRes + 1) == '\0')
				pRes = UCHAR_CONSTANT("_");
			else
				pRes = UCHAR_CONSTANT("_.");;
			if(*pbMustBeFreed == 1)
				free(pTmp);
			*pbMustBeFreed = 0;
		} else if(*pRes == '\0') {
			if(*pbMustBeFreed == 1)
				free(pRes);
			pRes = UCHAR_CONSTANT("_");
			bufLen = 1;
			*pbMustBeFreed = 0;
		}
	}


	if(pTpe->data.field.options.bDropLastLF && !pTpe->data.field.options.bEscapeCC) {
		int iLn;
		uchar *pB;
		if(bufLen == -1)
			bufLen = ustrlen(pRes);
		iLn = bufLen;
		if(iLn > 0 && *(pRes + iLn - 1) == '\n') {


			if(*pbMustBeFreed == 0) {

				pB = MALLOC((iLn + 1) * sizeof(uchar));
				if(pB == NULL) {
					RET_OUT_OF_MEMORY;
				}
				memcpy(pB, pRes, iLn - 1);
				pRes = pB;
				*pbMustBeFreed = 1;
			}
			*(pRes + iLn - 1) = '\0';
			--bufLen;
		}
	}


	if(pTpe->data.field.options.bCSV) {

		int iBufLen;
		uchar *pBStart;
		uchar *pDst;
		uchar *pSrc;
		if(bufLen == -1)
			bufLen = ustrlen(pRes);
		iBufLen = bufLen;

		pBStart = pDst = MALLOC((2 * iBufLen + 3) * sizeof(uchar));
		if(pDst == NULL) {
			if(*pbMustBeFreed == 1)
				free(pRes);
			RET_OUT_OF_MEMORY;
		}
		pSrc = pRes;
		*pDst++ = '"';
		while(*pSrc) {
			if(*pSrc == '"')
				*pDst++ = '"';
			*pDst++ = *pSrc++;
		}
		*pDst++ = '"';
		*pDst = '\0';
		if(*pbMustBeFreed == 1)
			free(pRes);
		pRes = pBStart;
		bufLen = -1;
		*pbMustBeFreed = 1;
	}

	if(bufLen == -1)
		bufLen = ustrlen(pRes);
	*pPropLen = bufLen;

	ENDfunc
	return(pRes);
}
