getKey()
{

    key::code key = gnash::key::INVALID;

    byte_t buf[LIRC_PACKET_SIZE];
    memset(buf, 0, LIRC_PACKET_SIZE);


    readNet(buf, LIRC_PACKET_SIZE, TIMEOUT);

    string packet = reinterpret_cast<char *>(buf);
    string::size_type space1 = packet.find(" ") +1;
    string::size_type space2 = packet.find(" ", space1) + 1;
    string::size_type space3 = packet.find(" ", space2) +1;

    string code_str = packet.substr(0, space1);
    string count_str = packet.substr(space1, space2-space1);
    string button_str = packet.substr(space2,space3-space2);
    string control_str = packet.substr(space3);

    if (button_str[0] > 'A' && button_str[0] < 'Z') {
        std::cerr << "Character: " << button_str << std::endl;
        key = (gnash::key::code)button_str[0];
    }

    return key;
}
