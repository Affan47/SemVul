static rpmRC hdrblobVerifyInfo(hdrblob blob, char **emsg)
{
    struct entryInfo_s info;
    int i, len = 0;
    int32_t end = 0;
    const char *ds = (const char *) blob->dataStart;
    int32_t il = (blob->regionTag) ? blob->il-1 : blob->il;
    entryInfo pe = (blob->regionTag) ? blob->pe+1 : blob->pe;

    int typechk = (blob->regionTag == RPMTAG_HEADERIMMUTABLE ||
		   blob->regionTag == RPMTAG_HEADERIMAGE);

    for (i = 0; i < il; i++) {
	ei2h(&pe[i], &info);


	if (end > info.offset)
	    goto err;

	if (hdrchkTag(info.tag))
	    goto err;
	if (hdrchkType(info.type))
	    goto err;
	if (hdrchkCount(info.count))
	    goto err;
	if (hdrchkAlign(info.type, info.offset))
	    goto err;
	if (hdrchkRange(blob->dl, info.offset))
	    goto err;
	if (typechk && hdrchkTagType(info.tag, info.type))
	    goto err;


	len = dataLength(info.type, ds + info.offset,
			 info.count, 1, ds + blob->dl);
	if (hdrchkRange(blob->dl - info.offset, len))
	    goto err;
	end = info.offset + len;
	if (blob->regionTag) {


	    if (end > blob->rdl - REGION_TAG_COUNT && info.offset < blob->rdl)
		goto err;
	}
    }
    return 0;

err:
    if (emsg) {
	rasprintf(emsg,
		  _("tag[%d]: BAD, tag %d type %d offset %d count %d len %d"),
		    i, info.tag, info.type, info.offset, info.count, len);
    }
    return i + 1;
}
