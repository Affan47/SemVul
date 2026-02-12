void APar_Extract_esds_Info(char *uint32_buffer,
                            FILE *isofile,
                            short track_level_atom,
                            TrackInfo *track_info) {
  uint64_t offset_into_stsd = 0;

  while (offset_into_stsd < parsedAtoms[track_level_atom].AtomicLength) {
    offset_into_stsd++;
    if (APar_read32(uint32_buffer,
                    isofile,
                    parsedAtoms[track_level_atom].AtomicStart +
                        offset_into_stsd) == 0x65736473) {
      track_info->contains_esds = true;

      uint64_t esds_start =
          parsedAtoms[track_level_atom].AtomicStart + offset_into_stsd - 4;
      uint64_t esds_length = APar_read32(uint32_buffer, isofile, esds_start);
      uint64_t offset_into_esds =
          12;

      if (APar_read8(isofile, esds_start + offset_into_esds) == 0x03) {
        offset_into_esds++;
        offset_into_esds +=
            APar_skip_filler(isofile, esds_start + offset_into_esds);
      }

      uint8_t section3_length =
          APar_read8(isofile, esds_start + offset_into_esds);
      if (section3_length <= esds_length && section3_length != 0) {
        track_info->section3_length = section3_length;
      } else {
        break;
      }


      uint8_t test_byte =
          APar_read8(isofile, esds_start + offset_into_esds + 1);
      if (test_byte != 0) {
        offset_into_esds++;
      }

      offset_into_esds += 4;

      if (APar_read8(isofile, esds_start + offset_into_esds) == 0x04) {
        offset_into_esds++;
        offset_into_esds +=
            APar_skip_filler(isofile, esds_start + offset_into_esds);
      }

      uint8_t section4_length =
          APar_read8(isofile, esds_start + offset_into_esds);
      if (section4_length <= section3_length && section4_length != 0) {
        track_info->section4_length = section4_length;

        if (section4_length == 0x9D)
          offset_into_esds++;


        offset_into_esds++;
        track_info->ObjectTypeIndication =
            APar_read8(isofile, esds_start + offset_into_esds);


        uint8_t a_v_flag =
            APar_read8(isofile,
                       esds_start + offset_into_esds +
                           1);


        if (track_info->ObjectTypeIndication < 0xC0 &&
            a_v_flag < 0xA0) {

          offset_into_esds += 5;
          track_info->max_bitrate = APar_read32(
              uint32_buffer, isofile, esds_start + offset_into_esds);
          offset_into_esds += 4;
          track_info->avg_bitrate = APar_read32(
              uint32_buffer, isofile, esds_start + offset_into_esds);
          offset_into_esds += 4;
        }
      } else {
        break;
      }

      if (APar_read8(isofile, esds_start + offset_into_esds) == 0x05) {
        offset_into_esds++;
        offset_into_esds +=
            APar_skip_filler(isofile, esds_start + offset_into_esds);

        uint8_t section5_length =
            APar_read8(isofile, esds_start + offset_into_esds);
        if ((section5_length <= section4_length || section4_length == 1) &&
            section5_length != 0) {
          track_info->section5_length = section5_length;
          offset_into_esds += 1;

          if (track_info->type_of_track & AUDIO_TRACK) {
            uint8_t packed_objID = APar_read8(
                isofile,
                esds_start + offset_into_esds);

            track_info->descriptor_object_typeID = packed_objID >> 3;
            offset_into_esds += 1;

            track_info->channels = (uint16_t)APar_ExtractChannelInfo(
                isofile, esds_start + offset_into_esds);

          } else if (track_info->type_of_track & VIDEO_TRACK) {


            if (APar_read16(uint32_buffer,
                            isofile,
                            esds_start + offset_into_esds + 2) == 0x01B0) {
              track_info->m4v_profile =
                  APar_read8(isofile, esds_start + offset_into_esds + 2 + 2);
            }
          }
        }
        break;
      }
    }
    if (offset_into_stsd > parsedAtoms[track_level_atom].AtomicLength) {
      break;
    }
  }
  if ((track_info->section5_length == 0 &&
       track_info->type_of_track & AUDIO_TRACK) ||
      track_info->channels == 0) {
    track_info->channels = APar_read16(
        uint32_buffer, isofile, parsedAtoms[track_level_atom].AtomicStart + 40);
  }
  return;
}
