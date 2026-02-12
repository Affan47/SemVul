void RtmpProtocol::handle_C1_complex(const char *data){


    const char *c1_start = data + 1;
    const char *schema_start = c1_start + 8;
    char *digest_start;
    try {


        auto digest = get_C1_digest((uint8_t *) schema_start + C1_SCHEMA_SIZE, &digest_start);
        string c1_joined(c1_start, C1_HANDSHARK_SIZE);
        c1_joined.erase(digest_start - c1_start, C1_DIGEST_SIZE);
        check_C1_Digest(digest, c1_joined);

        send_complex_S0S1S2(0, digest);

    } catch (std::exception &) {


        try {


            auto digest = get_C1_digest((uint8_t *) schema_start, &digest_start);
            string c1_joined(c1_start, C1_HANDSHARK_SIZE);
            c1_joined.erase(digest_start - c1_start, C1_DIGEST_SIZE);
            check_C1_Digest(digest, c1_joined);

            send_complex_S0S1S2(1, digest);

        } catch (std::exception &) {

            handle_C1_simple(data);
        }
    }
}
