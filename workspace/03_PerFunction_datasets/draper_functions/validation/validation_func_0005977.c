VarGetPattern(VarParser *vp, int delim, int *flags, VarPattern *patt)
{
	Buffer		*buf;

	buf = Buf_Init(0);


	while (*vp->ptr != '\0') {
		if (*vp->ptr == delim) {
			return (buf);

		} else if ((vp->ptr[0] == '\\') &&
		    ((vp->ptr[1] == delim) ||
		     (vp->ptr[1] == '\\') ||
		     (vp->ptr[1] == '$') ||
		     (vp->ptr[1] == '&' && patt != NULL))) {
			vp->ptr++;
			Buf_AddByte(buf, (Byte)vp->ptr[0]);
			vp->ptr++;

		} else if (vp->ptr[0] == '$') {
			if (vp->ptr[1] == delim) {
				if (flags == NULL) {
					Buf_AddByte(buf, (Byte)vp->ptr[0]);
					vp->ptr++;
				} else {


					*flags |= VAR_MATCH_END;
					vp->ptr++;
				}
			} else {
				VarParser	subvp = {
					vp->ptr,
					vp->ptr,
					vp->ctxt,
					vp->err,
					vp->execute
				};
				char   *rval;
				Boolean rfree;


				rval = VarParse(&subvp, &rfree);
				Buf_Append(buf, rval);
				if (rfree)
					free(rval);
				vp->ptr = subvp.ptr;
			}
		} else if (vp->ptr[0] == '&' && patt != NULL) {
			Buf_AppendBuf(buf, patt->lhs);
			vp->ptr++;
		} else {
			Buf_AddByte(buf, (Byte)vp->ptr[0]);
			vp->ptr++;
		}
	}

	Buf_Destroy(buf, TRUE);
	return (NULL);
}
