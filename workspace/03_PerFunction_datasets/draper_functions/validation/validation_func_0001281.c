dump_monster_treasure(const char *name) {
    archetype *at;
    int found;

    found = 0;
    fprintf(logfile, "\n");
    for (at = first_archetype; at != NULL; at = at->next)
        if (!strcasecmp(at->clone.name, name) && at->clone.title == NULL) {
            fprintf(logfile, "treasures for %s (arch: %s)\n", at->clone.name, at->name);
            if (at->clone.randomitems != NULL)
                dump_monster_treasure_rec(at->clone.name, at->clone.randomitems->items, 1);
            else
                fprintf(logfile, "(nothing)\n");
            fprintf(logfile, "\n");
            found++;
        }
    if (found == 0)
        fprintf(logfile, "No objects have the name %s!\n\n", name);
}
