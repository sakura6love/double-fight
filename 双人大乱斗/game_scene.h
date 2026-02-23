#pragma once

#include<graphics.h>

#include "util.h"
#include "scene.h"
#include "player.h"
#include "platform.h"
#include "status_bar.h"
#include "scene_manager.h"
#include "gamedata.h"

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;
extern IMAGE img_winner_bar;

extern Camera main_camera;

extern std::vector<Platform> platform_list;

extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;

extern SceneManager scene_manager;

extern GameData game_data;

class GameScene : public Scene
{
public:
	GameScene() = default;

	~GameScene() = default;

	void on_enter();

	void on_update(int delta);

	void on_draw(const Camera& camera);

	void on_input(const ExMessage& msg);

	void on_exit();

private:
	//图片位置
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };
	//玩家状态条
	StatusBar status_bar_1P;
	StatusBar status_bar_2P;

	bool is_game_over = false;

	//结算动效背景、文本位置
	POINT pos_img_winner_bar = { 0 };
	POINT pos_img_winner_text = { 0 };
	//移动的目标位置
	int pos_x_img_winner_bar_dst = 0;
	int pos_x_img_winner_text_dst = 0;
	//结算动效划入、划出定时器
	Timer timer_winner_slide_in;
	Timer timer_winner_slide_out;
	bool is_slide_out_started = false;

	//结束动画播放速度
	int speed_winner_bar = 250;
	int speed_winner_text = 150;

	int winner = 0; // 0: 无, 1: P1获胜, 2: P2获胜
};
