make_choice (std::string label, std::vector<std::string> v)
{
    size_t n;

    glk_window_clear(inputwin);

    glk_put_cstring(label.c_str());
    glk_put_char(0x0a);
    n = v.size();
    for(size_t i=0; i<n; ++i) {
        std::stringstream t;
        std::string s;
        t << i+1;
        t >> s;
        glk_put_cstring(s.c_str());
        glk_put_cstring(": ");
        glk_put_cstring(v[i].c_str());
        glk_put_cstring("\n");
    }

    std::stringstream t;
    std::string s;
    std::string s1;
    t << n;
    t >> s;
    s1 = "Choose [1-" + s + "]> ";
    glk_put_string_stream(inputwinstream, (char *)(s1.c_str()));

    int choice = 1;
    char buf[200];
    glk_request_line_event(inputwin, buf, (sizeof buf) - 1, 0);
    while(1) {
        event_t ev;

        glk_select(&ev);

        switch(ev.type) {
        case evtype_LineInput:
            if(ev.win == inputwin) {
                buf[ev.val1] = '\0';
                choice = atoi(buf);
                goto got_choice;
            }
            break;


        }
    }
got_choice:
    if(choice < 1) {
        choice = 1;
    }
    if((size_t)choice > n) {
        choice = n;
    }

    std::stringstream u;
    u << choice;
    u >> s;
    s1 = "Chosen: " +  s + "\n";
    glk_put_cstring(s1.c_str());

    return choice - 1;
}
