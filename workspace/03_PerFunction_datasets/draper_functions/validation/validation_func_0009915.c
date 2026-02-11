autosuggest_validate_from_history(const history_item_t &item, file_detection_context_t &detector, const wcstring &working_directory, const env_vars_snapshot_t &vars)
{
    ASSERT_IS_BACKGROUND_THREAD();

    bool handled = false, suggestionOK = false;


    wcstring parsed_command;
    wcstring_list_t parsed_arguments;
    int parsed_last_arg_pos = -1;
    if (! autosuggest_parse_command(item.str(), &parsed_command, &parsed_arguments, &parsed_last_arg_pos))
        return false;

    if (parsed_command == L"cd" && ! parsed_arguments.empty())
    {

        wcstring dir = parsed_arguments.back();
        if (expand_one(dir, EXPAND_SKIP_CMDSUBST))
        {
            handled = true;
            bool is_help = string_prefixes_string(dir, L"--help") || string_prefixes_string(dir, L"-h");
            if (is_help)
            {
                suggestionOK = false;
            }
            else
            {
                wcstring path;
                bool can_cd = path_get_cdpath(dir, &path, working_directory.c_str(), vars);
                if (! can_cd)
                {
                    suggestionOK = false;
                }
                else if (paths_are_same_file(working_directory, path))
                {

                    suggestionOK = false;
                }
                else
                {
                    suggestionOK = true;
                }
            }
        }
    }


    if (! handled)
    {
        bool cmd_ok = false;

        if (path_get_path(parsed_command, NULL))
        {
            cmd_ok = true;
        }
        else if (builtin_exists(parsed_command) || function_exists_no_autoload(parsed_command, vars))
        {
            cmd_ok = true;
        }

        if (cmd_ok)
        {
            const path_list_t &paths = item.get_required_paths();
            if (paths.empty())
            {
                suggestionOK= true;
            }
            else
            {
                detector.potential_paths = paths;
                suggestionOK = detector.paths_are_valid(paths);
            }
        }
    }

    return suggestionOK;
}
