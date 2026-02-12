static int reserve_dependencies(Unit *u, Unit *other, UnitDependency d) {
        unsigned n_reserve;

        assert(u);
        assert(other);
        assert(d < _UNIT_DEPENDENCY_MAX);


        if (!u->dependencies[d])
                return 0;


        n_reserve = hashmap_size(other->dependencies[d]) - !!hashmap_get(other->dependencies[d], u);

        return hashmap_reserve(u->dependencies[d], n_reserve);
}
