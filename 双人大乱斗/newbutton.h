#pragma once

#include"button.h"
#include"scene_manager.h"
#include "gamedata.h"

extern SceneManager scene_manager;

extern GameData game_data;

class NewButton :public Button {
public:
	NewButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR payh_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, payh_img_hovered, path_img_pushed) {
	}

	~NewButton() = default;

protected:
	void OnClick() override {
		game_data.reset();
		scene_manager.switch_to(SceneManager::SceneType::Selector);
	}
};