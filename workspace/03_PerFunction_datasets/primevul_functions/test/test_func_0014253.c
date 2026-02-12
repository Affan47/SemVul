void Statement::CleanQueue() {
    Napi::Env env = this->Env();
    Napi::HandleScope scope(env);

    if (prepared && !queue.empty()) {


        EXCEPTION(Napi::String::New(env, "Statement is already finalized"), SQLITE_MISUSE, exception);
        Napi::Value argv[] = { exception };
        bool called = false;


        while (!queue.empty()) {
            std::unique_ptr<Call> call(queue.front());
            queue.pop();

            std::unique_ptr<Baton> baton(call->baton);
            Napi::Function cb = baton->callback.Value();

            if (prepared && !cb.IsEmpty() &&
                cb.IsFunction()) {
                TRY_CATCH_CALL(Value(), cb, 1, argv);
                called = true;
            }
        }


        if (!called) {
            Napi::Value info[] = { Napi::String::New(env, "error"), exception };
            EMIT_EVENT(Value(), 2, info);
        }
    }
    else while (!queue.empty()) {


        std::unique_ptr<Call> call(queue.front());
        queue.pop();


        delete call->baton;
    }
}
