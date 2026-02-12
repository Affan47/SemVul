static void DecodeHeader(guchar *Data, gint Bytes,
			 struct ico_progressive_state *State,
			 GError **error)
{


	struct ico_direntry_data *entry;
	gint IconCount = 0;
	guchar *BIH;
 	guchar *Ptr;
 	gint I;
	guint16 imgtype;
	GList *l;


	if (((Data[1] << 8) + Data[0]) != 0) {
		g_set_error_literal (error,
				     GDK_PIXBUF_ERROR,
				     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
				     _("Invalid header in icon"));
		return;

	}

	imgtype = (Data[3] << 8) + Data[2];

	State->cursor = (imgtype == 2) ? TRUE : FALSE;


	if (!State->cursor && imgtype != 1) {
		g_set_error_literal (error,
				     GDK_PIXBUF_ERROR,
				     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
				     _("Invalid header in icon"));
		return;
	}


 	IconCount = (Data[5] << 8) + (Data[4]);

 	State->HeaderSize = 6 + IconCount*16;

 	if (State->HeaderSize>State->BytesInHeaderBuf) {
 		guchar *tmp=g_try_realloc(State->HeaderBuf,State->HeaderSize);
		if (!tmp) {
			g_set_error_literal (error,
                                             GDK_PIXBUF_ERROR,
                                             GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                             _("Not enough memory to load icon"));
			return;
		}
		State->HeaderBuf = tmp;
 		State->BytesInHeaderBuf = State->HeaderSize;
 	}
 	if (Bytes < State->HeaderSize) {
		g_set_error_literal (error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                     _("Not enough bytes for header"));
 		return;
	}


	g_list_free_full (State->entries, g_free);
	State->entries = 0;
	Ptr = Data + 6;
	for (I=0;I<IconCount;I++) {
		entry = g_new0 (struct ico_direntry_data, 1);
		entry->ImageScore = (Ptr[11] << 24) + (Ptr[10] << 16) + (Ptr[9] << 8) + (Ptr[8]);
		if (entry->ImageScore == 0)
			entry->ImageScore = 256;
		entry->x_hot = (Ptr[5] << 8) + Ptr[4];
		entry->y_hot = (Ptr[7] << 8) + Ptr[6];
		entry->DIBoffset = (Ptr[15]<<24)+(Ptr[14]<<16)+
		                   (Ptr[13]<<8) + (Ptr[12]);
		State->entries = g_list_insert_sorted (State->entries, entry, compare_direntry_scores);
		Ptr += 16;
	}


	entry = NULL;
	for (l = State->entries; l != NULL; l = g_list_next (l)) {
		entry = l->data;

		if (entry->DIBoffset < 0) {
			g_set_error_literal (error,
			                     GDK_PIXBUF_ERROR,
			                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
			                     _("Invalid header in icon"));
			return;
		}


		State->HeaderSize = entry->DIBoffset + 40;

		if (State->HeaderSize < 0) {
			g_set_error_literal (error,
			                     GDK_PIXBUF_ERROR,
			                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
			                     _("Invalid header in icon"));
			return;
		}

		if (State->HeaderSize>State->BytesInHeaderBuf) {
			guchar *tmp=g_try_realloc(State->HeaderBuf,State->HeaderSize);
			if (!tmp) {
				g_set_error_literal (error,
				                     GDK_PIXBUF_ERROR,
				                     GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
				                     _("Not enough memory to load icon"));
				return;
			}
			State->HeaderBuf = tmp;
			State->BytesInHeaderBuf = State->HeaderSize;
		}
		if (Bytes<State->HeaderSize)
			return;

		BIH = Data+entry->DIBoffset;


		if ((BIH[16] != 0) || (BIH[17] != 0) || (BIH[18] != 0)
		    || (BIH[19] != 0))
			continue;


		break;
	}


	if (l == NULL) {
		g_set_error_literal (error,
		                     GDK_PIXBUF_ERROR,
		                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
		                     _("Compressed icons are not supported"));
		return;
	}


	State->DIBoffset = entry->DIBoffset;
	State->x_hot = entry->x_hot;
	State->y_hot = entry->y_hot;

#ifdef DUMPBIH
	DumpBIH(BIH);
#endif


	State->Header.width =
	    (int)(BIH[7] << 24) + (BIH[6] << 16) + (BIH[5] << 8) + (BIH[4]);
	if (State->Header.width == 0)
		State->Header.width = 256;

	State->Header.height =
	    (int)((BIH[11] << 24) + (BIH[10] << 16) + (BIH[9] << 8) + (BIH[8]))/2;

	if (State->Header.height == 0)
		State->Header.height = 256;
	State->Header.depth = (BIH[15] << 8) + (BIH[14]);

	State->Type = State->Header.depth;
	if (State->Lines>=State->Header.height)
		State->Type = 1;


	I = (int)(BIH[35] << 24) + (BIH[34] << 16) + (BIH[33] << 8) + (BIH[32]);
	I = I*4;
	if ((I==0)&&(State->Type==1))
		I = 2*4;
	if ((I==0)&&(State->Type==4))
		I = 16*4;
	if ((I==0)&&(State->Type==8))
		I = 256*4;

	State->HeaderSize+=I;

	if (State->HeaderSize < 0) {
		g_set_error_literal (error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                     _("Invalid header in icon"));
		return;
	}

 	if (State->HeaderSize>State->BytesInHeaderBuf) {
	        guchar *tmp=g_try_realloc(State->HeaderBuf,State->HeaderSize);
		if (!tmp) {
			g_set_error_literal (error,
                                             GDK_PIXBUF_ERROR,
                                             GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                             _("Not enough memory to load icon"));
			return;
		}
		State->HeaderBuf = tmp;
 		State->BytesInHeaderBuf = State->HeaderSize;
 	}
 	if (Bytes < State->HeaderSize) {
		g_set_error_literal (error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                     _("Not enough bytes for header"));
 		return;
	}


	if (State->Header.height < 0) {
		State->Header.height = -State->Header.height;
		State->Header.Negative = 1;
	}
	if (State->Header.width < 0) {
		State->Header.width = -State->Header.width;
	}
	g_assert (State->Header.width > 0);
	g_assert (State->Header.height > 0);

        if (State->Type == 32)
                State->LineWidth = State->Header.width * 4;
        else if (State->Type == 24)
		State->LineWidth = State->Header.width * 3;
        else if (State->Type == 16)
                State->LineWidth = State->Header.width * 2;
        else if (State->Type == 8)
		State->LineWidth = State->Header.width * 1;
        else if (State->Type == 4)
		State->LineWidth = (State->Header.width+1)/2;
        else if (State->Type == 1) {
		State->LineWidth = State->Header.width / 8;
		if ((State->Header.width & 7) != 0)
			State->LineWidth++;
        } else {
          g_set_error_literal (error,
                               GDK_PIXBUF_ERROR,
                               GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                               _("Unsupported icon type"));
          return;
	}


	if (((State->LineWidth % 4) > 0))
		State->LineWidth = (State->LineWidth / 4) * 4 + 4;


	if (State->LineBuf == NULL) {
		State->LineBuf = g_try_malloc(State->LineWidth);
		if (!State->LineBuf) {
			g_set_error_literal (error,
                                             GDK_PIXBUF_ERROR,
                                             GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                             _("Not enough memory to load icon"));
			return;
		}
	}

	g_assert(State->LineBuf != NULL);


	if (State->pixbuf == NULL) {
#if 1
		if (State->size_func) {
			gint width = State->Header.width;
			gint height = State->Header.height;

			(*State->size_func) (&width, &height, State->user_data);
			if (width == 0 || height == 0) {
				State->LineWidth = 0;
				return;
			}
		}
#endif

		State->pixbuf =
		    gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8,
				   State->Header.width,
				   State->Header.height);
		if (!State->pixbuf) {
			g_set_error_literal (error,
                                             GDK_PIXBUF_ERROR,
                                             GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                             _("Not enough memory to load icon"));
			return;
		}
		if (State->cursor) {
			gchar hot[10];
			g_snprintf (hot, 10, "%d", State->x_hot);
			gdk_pixbuf_set_option (State->pixbuf, "x_hot", hot);
			g_snprintf (hot, 10, "%d", State->y_hot);
			gdk_pixbuf_set_option (State->pixbuf, "y_hot", hot);
		}

		if (State->prepared_func != NULL)

			(*State->prepared_func) (State->pixbuf,
                                                 NULL,
						 State->user_data);

	}

}
