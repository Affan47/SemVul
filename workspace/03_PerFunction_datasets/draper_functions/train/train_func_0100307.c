handshake(Json& request, threadinfo& ti) {
    always_assert(request.is_a() && request.size() >= 2
                  && request[1].is_i() && request[1].as_i() == Cmd_Handshake
                  && (request.size() == 2 || request[2].is_o()));
    if (request.size() >= 2
        && request[2]["maxkeylen"].is_i()
        && request[2]["maxkeylen"].as_i() > MASSTREE_MAXKEYLEN) {
        request[2] = false;
        request[3] = "bad maxkeylen";
        request.resize(4);
    } else {
        request[2] = true;
        request[3] = ti.index();
        request[4] = row_type::name();
        request.resize(5);
    }
    request[1] = Cmd_Handshake + 1;
    return request[2].as_b() ? 1 : -1;
}
