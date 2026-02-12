void unit_ref_unset(UnitRef *ref) {
        assert(ref);

        if (!ref->target)
                return;


        unit_add_to_gc_queue(ref->target);

        LIST_REMOVE(refs_by_target, ref->target->refs_by_target, ref);
        ref->source = ref->target = NULL;
}
