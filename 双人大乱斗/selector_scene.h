#pragma once

#include<graphics.h>

#include "scene.h"
#include "animation.h"
#include "player_id.h"
#include "scene_manager.h"
#include "sunflower_player.h"
#include "peashooter_player.h"

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_VS;
extern IMAGE img_1P;
extern IMAGE img_2P;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;
extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;
extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;
extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;
extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;
extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;

extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_right;

extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;

extern SceneManager scene_manager;

class SelectorScene : public Scene
{
public:
	SelectorScene() = default;

	~SelectorScene() = default;

	void on_enter();

	void on_update(int delta);

	void on_draw(const Camera& camera);

	void on_input(const ExMessage& msg);

	void on_exit();

private:
	enum class PlayerType
	{
		Peashooter = 0,
		Sunflower,
		Invalid
	};

private:
	POINT pos_img_VS = { 0 };						//VS艺术字图片位置
	POINT pos_img_tip = { 0 };						//提示信息文本图片位置
	POINT pos_img_1P = { 0 };						//1P 文本图片位置
	POINT pos_img_2P = { 0 };						//2P 文本图片位置
	POINT pos_img_1P_desc = { 0 };					//1P 键位描述图片位置
	POINT pos_img_2P_desc = { 0 };					//2P 键位描述图片位置
	POINT pos_img_1P_name = { 0 };					//1P 角色姓名文本位置
	POINT pos_img_2P_name = { 0 };					//2P 角色姓名文本位置
	POINT pos_animation_1P = { 0 };					//1P 角色动画位置
	POINT pos_animation_2P = { 0 };					//2P 角色动画位置
	POINT pos_img_1P_gravestone = { 0 };			//1P 墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };			//2P 墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 };			//1P 向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };		//1P 向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 };			//2P 向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };		//2P 向右切换按钮位置

	Animation animation_peashooter;
	Animation animation_sunflower;

	PlayerType player_type_1 = PlayerType::Peashooter;
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("豌豆射手");
	LPCTSTR str_sunflower_name = _T("向日葵");

	int selector_background_scorll_offset_x = 0;	//背景板滚动距离

	//1P、2P的左右切换按钮是否按下
	bool is_btn_1P_left_down = false;
	bool is_btn_1P_right_down = false;
	bool is_btn_2P_left_down = false;
	bool is_btn_2P_right_down = false;

private:
	//绘制带阴影的文本
	void outtextxy_shaded(int x, int y, LPCTSTR str);

};
