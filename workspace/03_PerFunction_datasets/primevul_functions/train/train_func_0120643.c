static int is_vms_varlen_txt(__G__ ef_buf, ef_len)
    __GDEF
    uch *ef_buf;
    unsigned ef_len;
{
    unsigned eb_id;
    unsigned eb_len;
    uch *eb_data;
    unsigned eb_datlen;
#define VMSREC_C_UNDEF  0
#define VMSREC_C_VAR    2
    uch vms_rectype = VMSREC_C_UNDEF;


#define VMSPK_ITEMID            0
#define VMSPK_ITEMLEN           2
#define VMSPK_ITEMHEADSZ        4

#define VMSATR_C_RECATTR        4
#define VMS_FABSIG              0x42414656

#define VMSFAB_B_RFM            31
#define VMSFAB_B_ORG            29

    if (ef_len == 0 || ef_buf == NULL)
        return FALSE;

    while (ef_len >= EB_HEADSIZE) {
        eb_id = makeword(EB_ID + ef_buf);
        eb_len = makeword(EB_LEN + ef_buf);

        if (eb_len > (ef_len - EB_HEADSIZE)) {

            Trace((stderr,
              "is_vms_varlen_txt: block length %u > rest ef_size %u\n", eb_len,
              ef_len - EB_HEADSIZE));
            break;
        }

        switch (eb_id) {
          case EF_PKVMS:


            eb_data = ef_buf+(EB_HEADSIZE+4);
            eb_datlen = eb_len-4;


            if (makelong(ef_buf+EB_HEADSIZE) !=
                crc32(CRCVAL_INITIAL, eb_data, (extent)eb_datlen))
            {
                Info(slide, 1, ((char *)slide,
                  "[Warning: CRC error, discarding PKWARE extra field]\n"));

                break;
            }


            while (eb_datlen > 4)
            {
                unsigned fldsize = makeword(&eb_data[VMSPK_ITEMLEN]);


                switch (makeword(&eb_data[VMSPK_ITEMID])) {
                  case VMSATR_C_RECATTR:


                    if (fldsize >= 1) {
                        vms_rectype = eb_data[VMSPK_ITEMHEADSZ] & 15;

                    }
                    break;
                  default:
                    break;
                }

                eb_datlen -= fldsize + VMSPK_ITEMHEADSZ;
                eb_data += fldsize + VMSPK_ITEMHEADSZ;
            }
            break;

          case EF_IZVMS:
            if (makelong(ef_buf+EB_HEADSIZE) == VMS_FABSIG) {
                if ((eb_data = extract_izvms_block(__G__
                                                   ef_buf+EB_HEADSIZE, eb_len,
                                                   &eb_datlen, NULL, 0))
                    != NULL)
                {
                    if (eb_datlen >= VMSFAB_B_RFM+1) {
                        vms_rectype = eb_data[VMSFAB_B_RFM] & 15;

                    }
                    free(eb_data);
                }
            }
            break;

          default:
            break;
        }


        ef_buf += (eb_len + EB_HEADSIZE);
        ef_len -= (eb_len + EB_HEADSIZE);
    }

    return (vms_rectype == VMSREC_C_VAR);

}
