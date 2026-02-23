#pragma once

#include"button.h"
#include"scene_manager.h"

extern SceneManager scene_manager;

class ContinueButton :public Button {
public:
	ContinueButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR payh_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, payh_img_hovered, path_img_pushed) {
	}

	~ContinueButton() = default;

protected:
	void OnClick() override {
		scene_manager.switch_to(SceneManager::SceneType::Selector);
	}
};