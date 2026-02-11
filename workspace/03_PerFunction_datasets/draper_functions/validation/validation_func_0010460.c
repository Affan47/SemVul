newProgram(const char *name, ref<YIcon> icon,
                               const bool restart, const char *wmclass,
                               upath exe, YStringArray &args) {

    if (exe != null) {
        MSG(("LOOKING FOR: %s\n", cstring(exe.path()).c_str()));
        upath fullname = findPath(getenv("PATH"), X_OK, exe);
        if (fullname == null) {
            MSG(("Program %s (%s) not found.", name, cstring(exe.path()).c_str()));
            return 0;
        }

        DProgram *program =
            new DProgram(name, icon, restart, wmclass, fullname, args);

        return program;
    }
    return NULL;
}
