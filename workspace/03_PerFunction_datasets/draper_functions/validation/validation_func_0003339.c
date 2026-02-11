loadDefaults() {
    fbdbg<<"Loading default key bindings"<<endl;

    deleteTree();
    m_map["default:"] = FbTk::makeRef<t_key>();
    addBinding("OnDesktop Mouse1 :HideMenus");
    addBinding("OnDesktop Mouse2 :WorkspaceMenu");
    addBinding("OnDesktop Mouse3 :RootMenu");
    addBinding("OnTitlebar Mouse3 :WindowMenu");
    addBinding("OnWindow Mouse1 :MacroCmd {Focus} {Raise} {StartMoving}");
    addBinding("OnTitlebar Mouse1 :MacroCmd {Focus} {Raise} {ActivateTab}");
    addBinding("OnTitlebar Move1 :StartMoving");
    addBinding("OnLeftGrip Move1 :StartResizing bottomleft");
    addBinding("OnRightGrip Move1 :StartResizing bottomright");
    addBinding("OnWindowBorder Move1 :StartMoving");
    addBinding("Mod1 Tab :NextWindow (workspace=[current])");
    addBinding("Mod1 Shift Tab :PrevWindow (workspace=[current])");
    keyMode("default");
}
