void Statement::Work_AfterAll(napi_env e, napi_status status, void* data) {
    std::unique_ptr<RowsBaton> baton(static_cast<RowsBaton*>(data));
    Statement* stmt = baton->stmt;

    Napi::Env env = stmt->Env();
    Napi::HandleScope scope(env);

    if (stmt->status != SQLITE_DONE) {
        Error(baton.get());
    }
    else {

        Napi::Function cb = baton->callback.Value();
        if (!cb.IsUndefined() && cb.IsFunction()) {
            if (baton->rows.size()) {

                Napi::Array result(Napi::Array::New(env, baton->rows.size()));
                Rows::const_iterator it = baton->rows.begin();
                Rows::const_iterator end = baton->rows.end();
                for (int i = 0; it < end; ++it, i++) {
                    std::unique_ptr<Row> row(*it);
                    (result).Set(i, RowToJS(env,row.get()));
                }

                Napi::Value argv[] = { env.Null(), result };
                TRY_CATCH_CALL(stmt->Value(), cb, 2, argv);
            }
            else {

                Napi::Value argv[] = {
                    env.Null(),
                    Napi::Array::New(env, 0)
                };
                TRY_CATCH_CALL(stmt->Value(), cb, 2, argv);
            }
        }
    }

    STATEMENT_END();
}
