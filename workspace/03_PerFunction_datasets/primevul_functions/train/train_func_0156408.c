qtdemux_parse_node (GstQTDemux * qtdemux, GNode * node, const guint8 * buffer,
    guint length)
{
  guint32 fourcc = 0;
  guint32 node_length = 0;
  const QtNodeType *type;
  const guint8 *end;

  GST_LOG_OBJECT (qtdemux, "qtdemux_parse buffer %p length %u", buffer, length);

  if (G_UNLIKELY (length < 8))
    goto not_enough_data;

  node_length = QT_UINT32 (buffer);
  fourcc = QT_FOURCC (buffer + 4);


  if (G_UNLIKELY (fourcc == 0 || node_length == 8))
    return TRUE;

  type = qtdemux_type_get (fourcc);

  end = buffer + length;

  GST_LOG_OBJECT (qtdemux,
      "parsing '%" GST_FOURCC_FORMAT "', length=%u, name '%s'",
      GST_FOURCC_ARGS (fourcc), node_length, type->name);

  if (node_length > length)
    goto broken_atom_size;

  if (type->flags & QT_FLAG_CONTAINER) {
    qtdemux_parse_container (qtdemux, node, buffer + 8, end);
  } else {
    switch (fourcc) {
      case FOURCC_stsd:
      {
        if (node_length < 20) {
          GST_LOG_OBJECT (qtdemux, "skipping small stsd box");
          break;
        }
        GST_DEBUG_OBJECT (qtdemux,
            "parsing stsd (sample table, sample description) atom");

        qtdemux_parse_container (qtdemux, node, buffer + 16, end);
        break;
      }
      case FOURCC_mp4a:
      case FOURCC_alac:
      case FOURCC_fLaC:
      {
        guint32 version;
        guint32 offset;
        guint min_size;


        if (fourcc == FOURCC_mp4a)
          min_size = 20;
        else if (fourcc == FOURCC_fLaC)
          min_size = 86;
        else
          min_size = 40;


        if (length < min_size) {
          GST_LOG_OBJECT (qtdemux, "skipping small %" GST_FOURCC_FORMAT " box",
              GST_FOURCC_ARGS (fourcc));
          break;
        }


        version = QT_UINT16 (buffer + 16);

        GST_DEBUG_OBJECT (qtdemux, "%" GST_FOURCC_FORMAT " version 0x%08x",
            GST_FOURCC_ARGS (fourcc), version);


        switch (version) {
          case 0:
            offset = 0x24;
            break;
          case 1:
            offset = 0x34;
            break;
          case 2:
            offset = 0x48;
            break;
          default:
            GST_WARNING_OBJECT (qtdemux,
                "unhandled %" GST_FOURCC_FORMAT " version 0x%08x",
                GST_FOURCC_ARGS (fourcc), version);
            offset = 0;
            break;
        }
        if (offset)
          qtdemux_parse_container (qtdemux, node, buffer + offset, end);
        break;
      }
      case FOURCC_mp4v:
      case FOURCC_MP4V:
      case FOURCC_fmp4:
      case FOURCC_FMP4:
      case FOURCC_apcs:
      case FOURCC_apch:
      case FOURCC_apcn:
      case FOURCC_apco:
      case FOURCC_ap4h:
      {
        const guint8 *buf;
        guint32 version;
        int tlen;


        GST_DEBUG_OBJECT (qtdemux, "parsing in %" GST_FOURCC_FORMAT,
            GST_FOURCC_ARGS (fourcc));
        version = QT_UINT32 (buffer + 16);
        GST_DEBUG_OBJECT (qtdemux, "version %08x", version);
        if (1 || version == 0x00000000) {
          buf = buffer + 0x32;


          tlen = QT_UINT8 (buf);
          GST_DEBUG_OBJECT (qtdemux, "tlen = %d", tlen);
          buf++;
          GST_DEBUG_OBJECT (qtdemux, "string = %.*s", tlen, (char *) buf);


          buf += 31;
          buf += 4;

          GST_MEMDUMP_OBJECT (qtdemux, "mp4v", buf, end - buf);

          qtdemux_parse_container (qtdemux, node, buf, end);
        }
        break;
      }
      case FOURCC_H264:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "H264", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_avc1:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "avc1", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_avc3:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "avc3", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_H265:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "H265", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_hvc1:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "hvc1", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_hev1:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "hev1", buffer, end - buffer);
        qtdemux_parse_container (qtdemux, node, buffer + 0x56, end);
        break;
      }
      case FOURCC_mjp2:
      {
        qtdemux_parse_container (qtdemux, node, buffer + 86, end);
        break;
      }
      case FOURCC_meta:
      {
        GST_DEBUG_OBJECT (qtdemux, "parsing meta atom");
        qtdemux_parse_container (qtdemux, node, buffer + 12, end);
        break;
      }
      case FOURCC_mp4s:
      {
        GST_MEMDUMP_OBJECT (qtdemux, "mp4s", buffer, end - buffer);

        qtdemux_parse_container (qtdemux, node, buffer + 16, end);
        break;
      }
      case FOURCC_XiTh:
      {
        guint32 version;
        guint32 offset;

        version = QT_UINT32 (buffer + 12);
        GST_DEBUG_OBJECT (qtdemux, "parsing XiTh atom version 0x%08x", version);

        switch (version) {
          case 0x00000001:
            offset = 0x62;
            break;
          default:
            GST_DEBUG_OBJECT (qtdemux, "unknown version 0x%08x", version);
            offset = 0;
            break;
        }
        if (offset)
          qtdemux_parse_container (qtdemux, node, buffer + offset, end);
        break;
      }
      case FOURCC_in24:
      {
        qtdemux_parse_container (qtdemux, node, buffer + 0x34, end);
        break;
      }
      case FOURCC_uuid:
      {
        qtdemux_parse_uuid (qtdemux, buffer, end - buffer);
        break;
      }
      case FOURCC_encv:
      {
        qtdemux_parse_container (qtdemux, node, buffer + 86, end);
        break;
      }
      case FOURCC_enca:
      {
        qtdemux_parse_container (qtdemux, node, buffer + 36, end);
        break;
      }
      default:
        if (!strcmp (type->name, "unknown"))
          GST_MEMDUMP ("Unknown tag", buffer + 4, end - buffer - 4);
        break;
    }
  }
  GST_LOG_OBJECT (qtdemux, "parsed '%" GST_FOURCC_FORMAT "'",
      GST_FOURCC_ARGS (fourcc));
  return TRUE;


not_enough_data:
  {
    GST_ELEMENT_ERROR (qtdemux, STREAM, DEMUX,
        (_("This file is corrupt and cannot be played.")),
        ("Not enough data for an atom header, got only %u bytes", length));
    return FALSE;
  }
broken_atom_size:
  {
    GST_ELEMENT_ERROR (qtdemux, STREAM, DEMUX,
        (_("This file is corrupt and cannot be played.")),
        ("Atom '%" GST_FOURCC_FORMAT "' has size of %u bytes, but we have only "
            "%u bytes available.", GST_FOURCC_ARGS (fourcc), node_length,
            length));
    return FALSE;
  }
}
