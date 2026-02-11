ob_describe(const object *op, const object *observer, char *buf, size_t size) {
    ob_methods *methods;

    for (methods = &type_methods[op->type]; methods; methods = methods->fallback) {
        if (methods->describe) {
            methods->describe(methods, op, observer, buf, size);
            return buf;
        }
    }
    buf[0] = '\0';
    return buf;
}
