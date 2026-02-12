void cql_server::response::serialize(const event::schema_change& event, uint8_t version)
{
    if (version >= 3) {
        write_string(to_string(event.change));
        write_string(to_string(event.target));
        write_string(event.keyspace);
        switch (event.target) {
        case event::schema_change::target_type::KEYSPACE:
            break;
        case event::schema_change::target_type::TYPE:
        case event::schema_change::target_type::TABLE:
            write_string(event.arguments[0]);
            break;
        case event::schema_change::target_type::FUNCTION:
        case event::schema_change::target_type::AGGREGATE:
            write_string(event.arguments[0]);
            write_string_list(std::vector<sstring>(event.arguments.begin() + 1, event.arguments.end()));
            break;
        }
    } else {
        switch (event.target) {


        case event::schema_change::target_type::TYPE:
        case event::schema_change::target_type::FUNCTION:
        case event::schema_change::target_type::AGGREGATE:


            write_string(to_string(event::schema_change::change_type::UPDATED));
            write_string(event.keyspace);
            write_string("");
            break;
        case event::schema_change::target_type::TABLE:
        case event::schema_change::target_type::KEYSPACE:
            write_string(to_string(event.change));
            write_string(event.keyspace);
            if (event.target == event::schema_change::target_type::TABLE) {
                write_string(event.arguments[0]);
            } else {
                write_string("");
            }
        }
    }
}
