static int16_t sn_coap_parser_options_count_needed_memory_multiple_option(uint8_t *packet_data_ptr, uint16_t packet_left_len, sn_coap_option_numbers_e option, uint16_t option_number_len)
{
    uint16_t ret_value              = 0;
    uint16_t message_left           = packet_left_len;
    uint8_t *start_ptr              = packet_data_ptr;


    while (message_left > 0) {
        if (option == COAP_OPTION_LOCATION_PATH && option_number_len > 255) {
            return -1;
        }
        if (option == COAP_OPTION_URI_PATH && option_number_len > 255) {
            return -1;
        }
        if (option == COAP_OPTION_URI_QUERY && option_number_len > 255) {
            return -1;
        }
        if (option == COAP_OPTION_LOCATION_QUERY && option_number_len > 255) {
            return -1;
        }
        if (option == COAP_OPTION_ACCEPT && option_number_len > 2) {
            return -1;
        }
        if (option == COAP_OPTION_ETAG && option_number_len > 8) {
            return -1;
        }


        int8_t ptr_check_result = sn_coap_parser_check_packet_ptr(packet_data_ptr,
                                                                  start_ptr,
                                                                  packet_left_len,
                                                                  option_number_len);
        if (ptr_check_result != 0) {
            return -1;
        }

        ret_value += option_number_len + 1;


        message_left = sn_coap_parser_move_packet_ptr(&packet_data_ptr,
                                                      start_ptr,
                                                      packet_left_len,
                                                      option_number_len);
        if(message_left == 0) {
            break;
        }


        if (((*packet_data_ptr) >> COAP_OPTIONS_OPTION_NUMBER_SHIFT) != 0) {
            break;
        }


        option_number_len = (*packet_data_ptr & 0x0F);


        message_left = sn_coap_parser_move_packet_ptr(&packet_data_ptr,
                                                      start_ptr,
                                                      packet_left_len,
                                                      1);


        int8_t option_parse_result = parse_ext_option(&option_number_len,
                                                      &packet_data_ptr,
                                                      start_ptr,
                                                      packet_left_len,
                                                      &message_left);
        if (option_parse_result != 0) {
            return -1;
        }
    }

    if (ret_value != 0) {
        return (ret_value - 1);
    } else {
        return 0;
    }
}
