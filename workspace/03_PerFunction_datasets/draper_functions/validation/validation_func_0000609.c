JS_SetContextDebugHooks(JSContext *cx, const JSDebugHooks *hooks)
{
    JS_ASSERT(hooks);
    if (hooks != &cx->runtime->globalDebugHooks && hooks != &js_NullDebugHooks)
        js_LeaveTrace(cx);

#ifdef JS_TRACER
    JS_LOCK_GC(cx->runtime);
#endif
    JSDebugHooks *old = const_cast<JSDebugHooks *>(cx->debugHooks);
    cx->debugHooks = hooks;
#ifdef JS_TRACER
    cx->updateJITEnabled();
    JS_UNLOCK_GC(cx->runtime);
#endif
    return old;
}
