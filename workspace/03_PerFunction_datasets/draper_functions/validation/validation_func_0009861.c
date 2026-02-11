showInstanceLocation(int ins, char *prefix) {
    char buffer[1000];

    if (admin[ins].location == 0)
        return;
    else {
        output(prefix);
        if (isALocation(admin[ins].location)) {
            output("at");
            say(admin[ins].location);
            sprintf(buffer, "[%d]", admin[ins].location);
            output(buffer);
        } else if (isContainer(admin[ins].location)) {

            if (isObject(admin[ins].location))
                output("in");
            else if (isActor(admin[ins].location))
                output("carried by");
            say(admin[ins].location);
            sprintf(buffer, "[%d]", admin[ins].location);
            output(buffer);

        } else
            output("Illegal location!");
    }
}
