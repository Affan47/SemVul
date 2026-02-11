APar_ShowMPEG4AACProfileInfo(TrackInfo* track_info) {
    if (track_info->descriptor_object_typeID == 1) {
        fprintf(stdout, "  MPEG-4 AAC Main Profile");
    }
    else if (track_info->descriptor_object_typeID == 2) {
        fprintf(stdout, "  MPEG-4 AAC Low Complexity Profile");
    }
    else if (track_info->descriptor_object_typeID == 3) {
        fprintf(stdout, "  MPEG-4 AAC Scaleable Sample Rate Profile");
    }
    else if (track_info->descriptor_object_typeID == 4) {
        fprintf(stdout, "  MPEG-4 AAC T/F Profile");
    }
    else if (track_info->descriptor_object_typeID == 5) {
        fprintf(stdout, "  MPEG-4 AAC T/F Main Profile");
    }
    else if (track_info->descriptor_object_typeID == 6) {
        fprintf(stdout, "  MPEG-4 AAC T/F LC Profile");
    }
    else if (track_info->descriptor_object_typeID == 7) {
        fprintf(stdout, "  MPEG-4 AAC TwinVQ Profile");
    }
    else if (track_info->descriptor_object_typeID == 8) {
        fprintf(stdout, "  MPEG-4 AAC CELP Profile");
    }
    else if (track_info->descriptor_object_typeID == 9) {
        fprintf(stdout, "  MPEG-4 AAC HVXC Profile");
    }
    else if (track_info->descriptor_object_typeID == 10) {
        fprintf(stdout, "  MPEG-4 AAC HILN Profile");
    }
    else if (track_info->descriptor_object_typeID == 11) {
        fprintf(stdout, "  MPEG-4 AAC TTSI Profile");
    }
    else if (track_info->descriptor_object_typeID == 12) {
        fprintf(stdout, "  MPEG-4 AAC Main Synthesis Profile");
    }
    else if (track_info->descriptor_object_typeID == 13) {
        fprintf(stdout, "  MPEG-4 AAC Wavetable Synthesis Profile");
    }
    return;
}
