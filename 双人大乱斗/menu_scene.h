#pragma once

#include<graphics.h>
#include<sstream>

#include "scene.h"
#include "scene_manager.h"
#include "gamedata.h"
#include "util.h"
#include "newbutton.h"
#include "continuebutton.h"

extern IMAGE img_menu_background;
extern IMAGE img_new_game_btn;
extern IMAGE img_continue_btn;
extern IMAGE img_new_game_btn_hover;
extern IMAGE img_continue_btn_hover;

extern SceneManager scene_manager;

extern GameData game_data;

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene() = default;

	void on_enter();

	void on_draw(const Camera& camera);

	void on_input(const ExMessage& msg);

private:
	NewButton* nbt = nullptr;
	ContinueButton* cnt = nullptr;
};
