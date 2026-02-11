welcome() const
{
    Config config(kConfigFile);
    config.set_userid(utils::generate_uuid());
    cerr << endl;
    mycerr << "You are using OkShell for the first time on this computer."
           << endl;
    mycerr << "Below are some things you need to know." << endl;
    mycerr << "\n";
    mycerr << "OkShell's " << boldface("cloud feature")
           << " (not active in current version)" << endl;
    mycerr << "allows you to backup you profile in the cloud, as well as\n";
    mycerr << "to learn commands from other people using OkShell." << endl;
    mycerr << "\n";
    string use_cloud = yes_no_input(
            "Enable cloud feature? You can turn it off later. [Y/n]", "y");
    if (use_cloud == "y")
    {
        config.set_cloud_on();
        mycerr << "Cloud ON" << endl;
    }
    else
    {
        config.set_cloud_off();
        mycerr << "Cloud OFF" << endl;
    }
    mycerr << "\n";
    mycerr << "You are ready to go! Below is your unique OkShell user ID,\n";
    mycerr << "you can use it to restore you profile on other computers.\n";
    mycerr << "\n";
    mycerr << "   " << config.get_userid() << endl;
    mycerr << "\n";
    mycerr << "What's next: Type `" << boldface("ok help")
           << "` to see how to use OkShell." << endl;
    cerr << endl;
}
