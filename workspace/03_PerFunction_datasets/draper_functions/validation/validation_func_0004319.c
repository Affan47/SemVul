is_dragon_pl(const object *op) {
    if (op != NULL
    && op->type == PLAYER
    && op->arch != NULL
    && op->arch->clone.race != NULL
    && strcmp(op->arch->clone.race, "dragon") == 0)
        return 1;
    return 0;
}
