parse_server_commandline_arguments(int argc, char* argv[], server_data* server) {


    if (argc < 4 || argc > 5) {
        log_error("invalid number of arguments: nim-server p N IsMisere [port]");
        return 0;
    }

    server->max_concurrent_players = strtol(argv[1], NULL, 10);
    server->initial_number_of_objects = strtol(argv[2], NULL, 10);
    if (strtol(argv[3], NULL, 10))
        server->game_type = TYPE__MIESERE;
    else
        server->game_type = TYPE__REGULAR;

    if (argc == 5)
        server->server_port = strtol(argv[4], NULL, 10);

    if (server->initial_number_of_objects > MAXIMUM_NUMBER_OF_OBJECTS) {
        log_error("too many objects: 0<=N<=%d", MAXIMUM_NUMBER_OF_OBJECTS);
        return 0;
    }

    if (server->initial_number_of_objects < 0) {
        log_error("too few objects: 0<=N<=%d", MAXIMUM_NUMBER_OF_OBJECTS);
        return 0;
    }

    if (server->max_concurrent_players > 9 || server->max_concurrent_players < 2) {
        log_error("invalid number of players: 2<=p<=9");
        return 0;
    }

    log_debug("game_type=%d, server_port=%d, objects=%d", server->game_type, server->server_port,
            server->initial_number_of_objects);
    return 1;
}
