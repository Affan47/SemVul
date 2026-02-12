ptp_pack_OPL (PTPParams *params, MTPProperties *props, int nrofprops, unsigned char** opldataptr)
{
	unsigned char* opldata;
	MTPProperties *propitr;
	unsigned char *packedprops[MAX_MTP_PROPS];
	uint32_t packedpropslens[MAX_MTP_PROPS];
	uint32_t packedobjecthandles[MAX_MTP_PROPS];
	uint16_t packedpropsids[MAX_MTP_PROPS];
	uint16_t packedpropstypes[MAX_MTP_PROPS];
	uint32_t totalsize = 0;
	uint32_t bufp = 0;
	uint32_t noitems = 0;
	uint32_t i;

	totalsize = sizeof(uint32_t);
	propitr = props;
	while (nrofprops-- && noitems < MAX_MTP_PROPS) {

		packedobjecthandles[noitems]=propitr->ObjectHandle;
		totalsize += sizeof(uint32_t);

		packedpropsids[noitems]=propitr->property;
		totalsize += sizeof(uint16_t);

		packedpropstypes[noitems]= propitr->datatype;
		totalsize += sizeof(uint16_t);

	        packedpropslens[noitems] = ptp_pack_DPV (params, &propitr->propval, &packedprops[noitems], propitr->datatype);
		totalsize += packedpropslens[noitems];
		noitems ++;
		propitr ++;
	}


	opldata = malloc(totalsize);

	htod32a(&opldata[bufp],noitems);
	bufp += 4;


	for (i = 0; i < noitems; i++) {

		htod32a(&opldata[bufp],packedobjecthandles[i]);
		bufp += sizeof(uint32_t);
		htod16a(&opldata[bufp],packedpropsids[i]);
		bufp += sizeof(uint16_t);
		htod16a(&opldata[bufp],packedpropstypes[i]);
		bufp += sizeof(uint16_t);

		memcpy(&opldata[bufp], packedprops[i], packedpropslens[i]);
		bufp += packedpropslens[i];
		free(packedprops[i]);
	}
	*opldataptr = opldata;
	return totalsize;
}
