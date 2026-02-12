void APar_ExtractTrackDetails(char *uint32_buffer,
                              FILE *isofile,
                              Trackage *track,
                              TrackInfo *track_info) {
  uint64_t _offset = 0;

  APar_TrackLevelInfo(track, "tkhd");
  if (APar_read8(isofile, parsedAtoms[track->track_atom].AtomicStart + 8) ==
      0) {
    if (APar_read8(isofile, parsedAtoms[track->track_atom].AtomicStart + 11) &
        1) {
      track_info->track_enabled = true;
    }
    track_info->creation_time =
        APar_read32(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 12);
    track_info->modified_time =
        APar_read32(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 16);
    track_info->duration =
        APar_read32(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 28);
  } else {
    track_info->creation_time =
        APar_read64(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 12);
    track_info->modified_time =
        APar_read64(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 20);
    track_info->duration =
        APar_read64(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom].AtomicStart + 36);
  }


  APar_TrackLevelInfo(track, "mdhd");
  memset(uint32_buffer, 0, 5);
  uint16_t packed_language = APar_read16(
      uint32_buffer, isofile, parsedAtoms[track->track_atom].AtomicStart + 28);
  memset(track_info->unpacked_lang, 0, 4);
  APar_UnpackLanguage(
      track_info->unpacked_lang,
      packed_language);


  APar_TrackLevelInfo(track, "hdlr");
  memset(uint32_buffer, 0, 5);
  track_info->track_type = APar_read32(
      uint32_buffer, isofile, parsedAtoms[track->track_atom].AtomicStart + 16);
  if (track_info->track_type == 0x736F756E) {
    track_info->type_of_track = AUDIO_TRACK;
  } else if (track_info->track_type == 0x76696465) {
    track_info->type_of_track = VIDEO_TRACK;
  }
  if (parsedAtoms[track->track_atom].AtomicLength > 34) {
    memset(track_info->track_hdlr_name, 0, sizeof(track_info->track_hdlr_name));
    APar_readX(track_info->track_hdlr_name,
               isofile,
               parsedAtoms[track->track_atom].AtomicStart + 32,
               std::min((uint64_t)sizeof(track_info->track_hdlr_name),
                        parsedAtoms[track->track_atom].AtomicLength - 32));
  }


  APar_TrackLevelInfo(track, "stsd");
  memset(uint32_buffer, 0, 5);
  track_info->track_codec = APar_read32(
      uint32_buffer, isofile, parsedAtoms[track->track_atom].AtomicStart + 20);

  if (track_info->type_of_track & VIDEO_TRACK) {
    track_info->video_width =
        APar_read16(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom + 1].AtomicStart + 32);
    track_info->video_height =
        APar_read16(uint32_buffer,
                    isofile,
                    parsedAtoms[track->track_atom + 1].AtomicStart + 34);
    track_info->macroblocks =
        (track_info->video_width / 16) * (track_info->video_height / 16);


    if (track_info->track_codec == 0x61766331 ||
        track_info->track_codec == 0x64726D69) {
      track_info->contains_esds = false;
      APar_TrackLevelInfo(track, "avcC");


      track_info->avc_version =
          APar_read8(isofile, parsedAtoms[track->track_atom].AtomicStart + 8);
      if (track_info->avc_version == 1) {
        track_info->profile =
            APar_read8(isofile, parsedAtoms[track->track_atom].AtomicStart + 9);


        track_info->level = APar_read8(
            isofile, parsedAtoms[track->track_atom].AtomicStart + 11);
      }


    } else if (track_info->track_codec == 0x73323633) {
      APar_TrackLevelInfo(track, "d263");
      if (memcmp(parsedAtoms[track->track_atom].AtomicName, "d263", 4) == 0) {
        APar_Extract_d263_Info(
            uint32_buffer, isofile, track->track_atom, track_info);
      }

    } else {
      APar_TrackLevelInfo(track, "esds");
      if (memcmp(parsedAtoms[track->track_atom].AtomicName, "esds", 4) == 0) {
        APar_Extract_esds_Info(
            uint32_buffer,
            isofile,
            track->track_atom - 1,
            track_info);

      } else if (track_info->track_codec == 0x73323633) {
        track_info->type_of_track = VIDEO_TRACK;
      } else if (track_info->track_codec == 0x73616D72 ||
                 track_info->track_codec == 0x73617762 ||
                 track_info->track_codec == 0x73617770 ||
                 track_info->track_codec ==
                     0x73766D72) {
        track_info->type_of_track = AUDIO_TRACK;
      } else {
        track_info->type_of_track = OTHER_TRACK;

      }
    }

  } else if (track_info->type_of_track & AUDIO_TRACK) {
    if (track_info->track_codec == 0x73616D72 ||
        track_info->track_codec == 0x73617762 ||
        track_info->track_codec == 0x73617770 ||
        track_info->track_codec ==
            0x73766D72) {
      APar_Extract_AMR_Info(
          uint32_buffer, isofile, track->track_atom + 2, track_info);

    } else if (track_info->track_codec == 0x73657663) {
      APar_TrackLevelInfo(track, "devc");
      if (memcmp(parsedAtoms[track->track_atom].AtomicName, "devc", 4) == 0) {
        APar_Extract_devc_Info(isofile, track->track_atom, track_info);
      }

    } else if (track_info->track_codec == 0x73716370) {
      APar_TrackLevelInfo(track, "dqcp");
      if (memcmp(parsedAtoms[track->track_atom].AtomicName, "dqcp", 4) == 0) {
        APar_Extract_devc_Info(isofile,
                               track->track_atom,
                               track_info);
      }

    } else if (track_info->track_codec == 0x73736D76) {
      APar_TrackLevelInfo(track, "dsmv");
      if (memcmp(parsedAtoms[track->track_atom].AtomicName, "dsmv", 4) == 0) {
        APar_Extract_devc_Info(isofile,
                               track->track_atom,
                               track_info);
      }

    } else {
      APar_Extract_esds_Info(
          uint32_buffer, isofile, track->track_atom, track_info);
    }
  }


  if ((track_info->type_of_track & AUDIO_TRACK ||
       track_info->type_of_track & VIDEO_TRACK) &&
      track_info->avg_bitrate == 0) {
    if (track_info->track_codec == 0x616C6163) {
      track_info->channels =
          APar_read16(uint32_buffer,
                      isofile,
                      parsedAtoms[track->track_atom + 1].AtomicStart + 24);
    }
  }

  APar_TrackLevelInfo(track, "stsz");
  if (memcmp(parsedAtoms[track->track_atom].AtomicName, "stsz", 4) == 0) {
    track_info->sample_aggregate =
        calcuate_sample_size(uint32_buffer, isofile, track->track_atom);
  }


  if (track_info->track_codec >= 0x64726D00 &&
      track_info->track_codec <= 0x64726DFF) {
    track_info->type_of_track += DRM_PROTECTED_TRACK;
    APar_TrackLevelInfo(track, "frma");
    memset(uint32_buffer, 0, 5);
    track_info->protected_codec = APar_read32(
        uint32_buffer, isofile, parsedAtoms[track->track_atom].AtomicStart + 8);
  }


  if (track_info->contains_esds) {
    APar_TrackLevelInfo(track, "esds");


    _offset = APar_FindValueInAtom(
        uint32_buffer, isofile, track->track_atom, 24, 0x01B2);

    if (_offset > 0 && _offset < parsedAtoms[track->track_atom].AtomicLength) {
      _offset += 2;
      memset(track_info->encoder_name,
             0,
             parsedAtoms[track->track_atom].AtomicLength - _offset);
      APar_readX(track_info->encoder_name,
                 isofile,
                 parsedAtoms[track->track_atom].AtomicStart + _offset,
                 parsedAtoms[track->track_atom].AtomicLength - _offset);
    }
  }
  return;
}
