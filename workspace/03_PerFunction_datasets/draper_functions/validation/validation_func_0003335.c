parse(XML_PARSER& xp) {
    while (!xp.get_tag()) {
        if (xp.match_tag("/persistent_file_xfer")) return 0;
        else if (xp.parse_int("num_retries", nretry)) continue;
        else if (xp.parse_double("first_request_time", first_request_time)) {
            continue;
        }
        else if (xp.parse_double("next_request_time", next_request_time)) {
            continue;
        }
        else if (xp.parse_double("time_so_far", time_so_far)) continue;
        else if (xp.parse_double("last_bytes_xferred", last_bytes_xferred)) continue;
        else if (xp.parse_bool("is_upload", is_upload)) continue;
        else {
            if (log_flags.unparsed_xml) {
                msg_printf(NULL, MSG_INFO,
                    "[unparsed_xml] Unparsed line in file transfer info: %s",
                    xp.parsed_tag
                );
            }
        }
    }
    return ERR_XML_PARSE;
}
