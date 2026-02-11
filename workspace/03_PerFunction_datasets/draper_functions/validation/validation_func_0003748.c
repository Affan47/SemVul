drawActions(float dt) {
    if(gGourceSettings.hide_users) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, beamtex->textureid);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(!gGourceSettings.ffp) {

        action_vbo.draw();

    } else {


        for(std::map<std::string,RUser*>::iterator it = users.begin(); it!=users.end(); it++) {
            it->second->drawActions(dt);
        }
    }
}
