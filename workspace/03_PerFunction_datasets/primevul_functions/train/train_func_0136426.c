mime_decode_base64(FILE * in, FILE * out, uschar * boundary)
{
uschar ibuf[MIME_MAX_LINE_LENGTH], obuf[MIME_MAX_LINE_LENGTH];
uschar *ipos, *opos;
ssize_t len, size = 0;
int bytestate = 0;

opos = obuf;

while (Ufgets(ibuf, MIME_MAX_LINE_LENGTH, in) != NULL)
  {
  if (boundary != NULL
     && Ustrncmp(ibuf, "--", 2) == 0
     && Ustrncmp((ibuf+2), boundary, Ustrlen(boundary)) == 0
     )
    break;

  for (ipos = ibuf ; *ipos != '\r' && *ipos != '\n' && *ipos != 0; ++ipos)
    if (*ipos == '=')
      ++bytestate;

    else if (mime_b64[*ipos] == 128)
      mime_set_anomaly(MIME_ANOMALY_BROKEN_BASE64);


    else switch((bytestate++) & 3)
      {
      case 0:
	*opos = mime_b64[*ipos] << 2; break;
      case 1:
	*opos++ |= mime_b64[*ipos] >> 4;
	*opos = mime_b64[*ipos] << 4; break;
      case 2:
	*opos++ |= mime_b64[*ipos] >> 2;
	*opos = mime_b64[*ipos] << 6; break;
      case 3:
	*opos++ |= mime_b64[*ipos]; break;
      }


  len = opos - obuf;
  if (len > 0)
    {
    if (fwrite(obuf, 1, len, out) != len) return -1;
    size += len;

    if ((bytestate & 3) != 0)
      *obuf = *opos;
    opos = obuf;
    }
  }


if (bytestate & 3)
  {
  if (fwrite(obuf, 1, 1, out) != 1) return -1;
  ++size;
  }

return size;
}
