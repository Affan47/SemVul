runInheritedInitialize(Aint theClass) {
    if (theClass == 0) return;
    runInheritedInitialize(classes[theClass].parent);
    if (classes[theClass].initialize)
        interpret(classes[theClass].initialize);
}
