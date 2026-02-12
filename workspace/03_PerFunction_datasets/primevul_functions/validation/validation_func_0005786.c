TEST(TestAddDelegateOwnership, AddDelegateDoesNotTakeOwnership) {
  class TestDelegate : public TfLiteDelegate {
   public:
    TestDelegate(bool* destroyed, bool* prepared)
        : TfLiteDelegate(TfLiteDelegateCreate()),
          destroyed_(destroyed),
          prepared_(prepared) {
      flags = kTfLiteDelegateFlagsNone;
      Prepare = [](TfLiteContext*, TfLiteDelegate* delegate) -> TfLiteStatus {
        *(static_cast<TestDelegate*>(delegate)->prepared_) = true;
        return kTfLiteOk;
      };
    }
    ~TestDelegate() { *destroyed_ = true; }

   private:
    bool* destroyed_;
    bool* prepared_;
  };


  bool destroyed = false;
  bool prepared = false;
  {
    std::unique_ptr<TestDelegate> delegate(
        new TestDelegate(&destroyed, &prepared));
    {

      auto model = FlatBufferModel::BuildFromFile(
          "tensorflow/lite/testdata/empty_model.bin");
      ASSERT_TRUE(model);

      std::unique_ptr<Interpreter> interpreter;
      InterpreterBuilder builder(*model, TrivialResolver());
      builder.AddDelegate(delegate.get());

      for (int i = 0; i < 3; i++) {
        prepared = false;
        ASSERT_EQ(builder(&interpreter), kTfLiteOk);
        ASSERT_NE(interpreter, nullptr);


        EXPECT_TRUE(prepared);
        EXPECT_FALSE(destroyed);


        interpreter->AllocateTensors();
        interpreter->Invoke();
        EXPECT_FALSE(destroyed);
      }
    }
    EXPECT_NE(delegate, nullptr);
    EXPECT_FALSE(destroyed);
  }


  EXPECT_TRUE(destroyed);
}
