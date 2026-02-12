get_time_value(proto_tree *tree, tvbuff_t *tvb, const gint start,
	       const gint length, const guint encoding, nstime_t *time_stamp,
	       const gboolean is_relative)
{
	guint32     tmpsecs;
	guint64     tmp64secs;
	guint64     todusecs;

	switch (encoding) {

		case ENC_TIME_SECS_NSECS|ENC_BIG_ENDIAN:


			if (length == 16) {
				time_stamp->secs  = (time_t)tvb_get_ntoh64(tvb, start);
				time_stamp->nsecs = (guint32)tvb_get_ntoh64(tvb, start+8);
			} else if (length == 12) {
				time_stamp->secs  = (time_t)tvb_get_ntoh64(tvb, start);
				time_stamp->nsecs = tvb_get_ntohl(tvb, start+8);
			} else if (length == 8) {
				time_stamp->secs  = (time_t)tvb_get_ntohl(tvb, start);
				time_stamp->nsecs = tvb_get_ntohl(tvb, start+4);
			} else if (length == 4) {


				time_stamp->secs  = (time_t)tvb_get_ntohl(tvb, start);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a timespec", length, (length < 4));
			}
			break;

		case ENC_TIME_SECS_NSECS|ENC_LITTLE_ENDIAN:


			if (length == 16) {
				time_stamp->secs  = (time_t)tvb_get_letoh64(tvb, start);
				time_stamp->nsecs = (guint32)tvb_get_letoh64(tvb, start+8);
			} else if (length == 12) {
				time_stamp->secs  = (time_t)tvb_get_letoh64(tvb, start);
				time_stamp->nsecs = tvb_get_letohl(tvb, start+8);
			} else if (length == 8) {
				time_stamp->secs  = (time_t)tvb_get_letohl(tvb, start);
				time_stamp->nsecs = tvb_get_letohl(tvb, start+4);
			} else if (length == 4) {


				time_stamp->secs  = (time_t)tvb_get_letohl(tvb, start);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a timespec", length, (length < 4));
			}
			break;

		case ENC_TIME_NTP|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);


			tmpsecs  = tvb_get_ntohl(tvb, start);
			if ((tmpsecs & 0x80000000) != 0)
				time_stamp->secs = (time_t)((gint64)tmpsecs - NTP_TIMEDIFF1900TO1970SEC);
			else
				time_stamp->secs = (time_t)((gint64)tmpsecs + NTP_TIMEDIFF1970TO2036SEC);

			if (length == 8) {


				time_stamp->nsecs = (int)(1000000000*(tvb_get_ntohl(tvb, start+4)/4294967296.0));
				if ((time_stamp->nsecs == 0) && (tmpsecs == 0)) {

					time_stamp->secs = 0;
				}
			} else if (length == 4) {


				if (tmpsecs == 0) {

					time_stamp->secs = 0;
				}
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an NTP time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_NTP|ENC_LITTLE_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);


			tmpsecs  = tvb_get_letohl(tvb, start);
			if ((tmpsecs & 0x80000000) != 0)
				time_stamp->secs = (time_t)((gint64)tmpsecs - NTP_TIMEDIFF1900TO1970SEC);
			else
				time_stamp->secs = (time_t)((gint64)tmpsecs + NTP_TIMEDIFF1970TO2036SEC);

			if (length == 8) {


				time_stamp->nsecs = (int)(1000000000*(tvb_get_letohl(tvb, start+4)/4294967296.0));
				if ((time_stamp->nsecs == 0) && (tmpsecs == 0)) {

					time_stamp->secs = 0;
				}
			} else if (length == 4) {


				if (tmpsecs == 0) {

					time_stamp->secs = 0;
				}
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an NTP time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_TOD|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);
			DISSECTOR_ASSERT(length == 8);

			if (length == 8) {
				todusecs  = tvb_get_ntoh64(tvb, start) >> 12;
				time_stamp->secs = (time_t)((todusecs  / 1000000) - EPOCH_DELTA_1900_01_01_00_00_00_UTC);
				time_stamp->nsecs = (int)((todusecs  % 1000000) * 1000);
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a TOD clock time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_TOD|ENC_LITTLE_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {
				todusecs  = tvb_get_letoh64(tvb, start) >> 12 ;
				time_stamp->secs = (time_t)((todusecs  / 1000000) - EPOCH_DELTA_1900_01_01_00_00_00_UTC);
				time_stamp->nsecs = (int)((todusecs  % 1000000) * 1000);
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a TOD clock time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_RTPS|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {
				time_stamp->secs = (time_t)tvb_get_ntohl(tvb, start);


				time_stamp->nsecs = (int)(1000000000*(tvb_get_ntohl(tvb, start+4)/4294967296.0));
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an RTPS time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_RTPS|ENC_LITTLE_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {
				time_stamp->secs = (time_t)tvb_get_letohl(tvb, start);


				time_stamp->nsecs = (int)(1000000000*(tvb_get_letohl(tvb, start+4)/4294967296.0));
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an RTPS time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_MIP6 | ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {


				tmp64secs = tvb_get_ntoh48(tvb, start);
				tmpsecs = tvb_get_ntohs(tvb, start + 6);
				tmpsecs <<= 16;

				if ((tmp64secs == 0) && (tmpsecs == 0)) {

					time_stamp->secs = 0;
					time_stamp->nsecs = 0;
				} else {
					time_stamp->secs = (time_t)tmp64secs;
					time_stamp->nsecs = (int)((tmpsecs / 4294967296.0) * 1000000000);
				}
			} else {
				time_stamp->secs = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an NTP time stamp", length, (length != 8));
			}
			break;

		case ENC_TIME_SECS_USECS|ENC_BIG_ENDIAN:


			if (length == 8) {
				time_stamp->secs  = (time_t)tvb_get_ntohl(tvb, start);
				time_stamp->nsecs = tvb_get_ntohl(tvb, start+4)*1000;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a timeval", length, (length < 4));
			}
			break;

		case ENC_TIME_SECS_USECS|ENC_LITTLE_ENDIAN:


			if (length == 8) {
				time_stamp->secs  = (time_t)tvb_get_letohl(tvb, start);
				time_stamp->nsecs = tvb_get_letohl(tvb, start+4)*1000;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a timeval", length, (length < 4));
			}
			break;

		case ENC_TIME_SECS|ENC_BIG_ENDIAN:
		case ENC_TIME_SECS|ENC_LITTLE_ENDIAN:


			if (length >= 1 && length <= 8) {
				time_stamp->secs  = (time_t)get_uint64_value(tree, tvb, start, length, encoding);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a time-in-seconds time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_MSECS|ENC_BIG_ENDIAN:
		case ENC_TIME_MSECS|ENC_LITTLE_ENDIAN:


			if (length >= 1 && length <= 8) {
				guint64 msecs;

				msecs = get_uint64_value(tree, tvb, start, length, encoding);
				time_stamp->secs  = (time_t)(msecs / 1000);
				time_stamp->nsecs = (int)(msecs % 1000)*1000000;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a time-in-milliseconds time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_RFC_3971|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {


				time_stamp->secs  = (time_t)tvb_get_ntoh48(tvb, start);


				time_stamp->nsecs = (int)(1000000000*(tvb_get_ntohs(tvb, start+6)/65536.0));
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an RFC 3971-style time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_RFC_3971|ENC_LITTLE_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {


				time_stamp->secs  = (time_t)tvb_get_letoh48(tvb, start+2);


				time_stamp->nsecs = (int)(1000000000*(tvb_get_letohs(tvb, start)/65536.0));
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an RFC 3971-style time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_SECS_NTP|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 4) {


				tmpsecs  = tvb_get_ntohl(tvb, start);
				if ((tmpsecs & 0x80000000) != 0)
					time_stamp->secs = (time_t)((gint64)tmpsecs - NTP_TIMEDIFF1900TO1970SEC);
				else
					time_stamp->secs = (time_t)((gint64)tmpsecs + NTP_TIMEDIFF1970TO2036SEC);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an NTP seconds-only time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_SECS_NTP|ENC_LITTLE_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);


			if (length == 4) {
				tmpsecs  = tvb_get_letohl(tvb, start);
				if ((tmpsecs & 0x80000000) != 0)
					time_stamp->secs = (time_t)((gint64)tmpsecs - NTP_TIMEDIFF1900TO1970SEC);
				else
					time_stamp->secs = (time_t)((gint64)tmpsecs + NTP_TIMEDIFF1970TO2036SEC);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an NTP seconds-only time stamp", length, (length < 4));
			}
			break;
		case ENC_TIME_MSEC_NTP | ENC_BIG_ENDIAN:


			if (length >= 1 && length <= 8) {
				guint64 msecs;

				msecs = get_uint64_value(tree, tvb, start, length, encoding);
				tmpsecs = (guint32)(msecs / 1000);


				if ((tmpsecs & 0x80000000) != 0)
					time_stamp->secs = (time_t)((gint64)tmpsecs - NTP_TIMEDIFF1900TO1970SEC);
				else
					time_stamp->secs = (time_t)((gint64)tmpsecs + NTP_TIMEDIFF1970TO2036SEC);
				time_stamp->nsecs = (int)(msecs % 1000)*1000000;
			}
			else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "a time-in-milliseconds NTP time stamp", length, (length < 4));
			}
			break;

		case ENC_TIME_CLASSIC_MAC_OS_SECS|ENC_BIG_ENDIAN:


			DISSECTOR_ASSERT(!is_relative);

			if (length == 8) {
				tmp64secs  = tvb_get_ntoh64(tvb, start);
				time_stamp->secs = (time_t)(gint64)(tmp64secs - EPOCH_DELTA_1904_01_01_00_00_00_UTC);
				time_stamp->nsecs = 0;
			} else if (length == 4) {
				tmpsecs  = tvb_get_ntohl(tvb, start);
				time_stamp->secs = (time_t)(gint32)(tmpsecs - EPOCH_DELTA_1904_01_01_00_00_00_UTC);
				time_stamp->nsecs = 0;
			} else {
				time_stamp->secs  = 0;
				time_stamp->nsecs = 0;
				report_type_length_mismatch(tree, "an MP4 time stamp", length, (length < 4));
			}
			break;

		default:
			DISSECTOR_ASSERT_NOT_REACHED();
			break;
	}
}
