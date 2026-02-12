bool unit_shall_confirm_spawn(Unit *u) {
        assert(u);

        if (manager_is_confirm_spawn_disabled(u->manager))
                return false;


        return !unit_get_exec_context(u)->same_pgrp;
}
