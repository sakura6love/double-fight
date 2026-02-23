#include"menu_scene.h"

MenuScene::MenuScene() 
{
	//按钮初始化
	RECT newstart, ctngame;
	newstart.left = (1280 - 192) / 2;
	newstart.right = newstart.left + 192;
	newstart.top = 430;
	newstart.bottom = newstart.top + 75;

	ctngame.left = (1280 - 192) / 2;
	ctngame.right = ctngame.left + 192;
	ctngame.top = 550;
	ctngame.bottom = ctngame.top + 75;

	nbt = new NewButton(newstart, _T("resources/ui_start_idle.png"), _T("resources/ui_start_hovered.png"), _T("resources/ui_start_pushed.png"));
	cnt = new ContinueButton(ctngame, _T("resources/ui_quit_idle.png"), _T("resources/ui_quit_hovered.png"), _T("resources/ui_quit_pushed.png"));
}

void MenuScene::on_enter() 
{
	mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
}

void MenuScene::on_draw(const Camera& camera)
{
	putimage(0, 0, &img_menu_background);
	
	nbt->Draw();
	cnt->Draw();

	//绘制统计数据
	int statsX = 50;
	int statsY = 500;

	settextcolor(RGB(255, 255, 255));
	settextstyle(24, 0, _T("IPix"));

	TCHAR statsText[256];
	_stprintf_s(statsText, _T("总游戏场次: %d"), game_data.totalGames);
	outtextxy(statsX, statsY, statsText);

	_stprintf_s(statsText, _T("1P 胜利: %d"), game_data.player1Wins);
	outtextxy(statsX, statsY + 40, statsText);

	_stprintf_s(statsText, _T("2P 胜利: %d"), game_data.player2Wins);
	outtextxy(statsX, statsY + 80, statsText);

	if (game_data.lastWinner > 0)
	{
		_stprintf_s(statsText, _T("上次胜利: P%d"), game_data.lastWinner);
		outtextxy(statsX, statsY + 120, statsText);
	}
}

void MenuScene::on_input(const ExMessage& msg)
{
	cnt->ProcessEvent(msg);
	nbt->ProcessEvent(msg);
}