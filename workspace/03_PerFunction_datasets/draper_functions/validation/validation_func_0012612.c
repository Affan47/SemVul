Interior (const char* msg) {
    const int space = Math::round(.5*ivcm);

    return new MarginFrame(
        new VBox(
            new HBox(new Message(msg), new HGlue),
            new VGlue(space),
            new HBox(
                new HGlue,
                new PushButton("  Yes  ", state, 'y'),
                new HGlue(space, 0),
                new PushButton("  No  ", state, 'n'),
                new HGlue(space, 0),
                new PushButton("Cancel", state, '\007'),
                new HGlue
            )
        ), space, space/2, 0
    );
}
