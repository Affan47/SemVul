static rpmRC hdrblobVerifyRegion(rpmTagVal regionTag, int exact_size,
			hdrblob blob, char **buf)
{
    rpmRC rc = RPMRC_FAIL;
    struct entryInfo_s trailer, einfo;
    unsigned char * regionEnd = NULL;


    if (blob->il < 1) {
	rasprintf(buf, _("region: no tags"));
	goto exit;
    }


    ei2h(blob->pe, &einfo);

    if (!regionTag && (einfo.tag == RPMTAG_HEADERSIGNATURES ||
		       einfo.tag == RPMTAG_HEADERIMMUTABLE ||
		       einfo.tag == RPMTAG_HEADERIMAGE)) {
	regionTag = einfo.tag;
    }


    if (!(einfo.tag == regionTag)) {
	rc = RPMRC_NOTFOUND;
	goto exit;
    }


    if (!(einfo.type == REGION_TAG_TYPE && einfo.count == REGION_TAG_COUNT)) {
	rasprintf(buf,
		_("region tag: BAD, tag %d type %d offset %d count %d"),
		einfo.tag, einfo.type, einfo.offset, einfo.count);
	goto exit;
    }


    if (hdrchkRange(blob->dl, einfo.offset + REGION_TAG_COUNT)) {
	rasprintf(buf,
		_("region offset: BAD, tag %d type %d offset %d count %d"),
		einfo.tag, einfo.type, einfo.offset, einfo.count);
	goto exit;
    }


    memset(&trailer, 0, sizeof(trailer));
    regionEnd = blob->dataStart + einfo.offset;

    (void) memcpy(&trailer, regionEnd, REGION_TAG_COUNT);
    blob->rdl = einfo.offset + REGION_TAG_COUNT;

    ei2h(&trailer, &einfo);

    if (regionTag == RPMTAG_HEADERSIGNATURES && einfo.tag == RPMTAG_HEADERIMAGE)
	einfo.tag = RPMTAG_HEADERSIGNATURES;
    if (!(einfo.tag == regionTag &&
	  einfo.type == REGION_TAG_TYPE && einfo.count == REGION_TAG_COUNT))
    {
	rasprintf(buf,
		_("region trailer: BAD, tag %d type %d offset %d count %d"),
		einfo.tag, einfo.type, einfo.offset, einfo.count);
	goto exit;
    }


    blob->ril = -(einfo.offset/sizeof(*blob->pe));

    if ((einfo.offset % sizeof(*blob->pe)) || hdrchkRange(blob->il, blob->ril) ||
					hdrchkRange(blob->dl, blob->rdl)) {
	rasprintf(buf, _("region %d size: BAD, ril %d il %d rdl %d dl %d"),
			regionTag, blob->ril, blob->il, blob->rdl, blob->dl);
	goto exit;
    }


    if (exact_size && !(blob->il == blob->ril && blob->dl == blob->rdl)) {
	rasprintf(buf,
		_("region %d: tag number mismatch il %d ril %d dl %d rdl %d\n"),
		regionTag, blob->il, blob->ril, blob->dl, blob->rdl);
	goto exit;
    }

    blob->regionTag = regionTag;
    rc = RPMRC_OK;

exit:
    return rc;
}
