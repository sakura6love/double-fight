#pragma once

#include<Windows.h>
#include<graphics.h>

enum class Status {
	Idle = 0,
	Hovered,
	Pushed
};

class Button {
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);

	~Button() = default;

	void Draw();

	void ProcessEvent(const ExMessage& msg);

private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;

	Status status = Status::Idle;

private:
	//¼ì²âÊó±êµã»÷
	bool CheckCursorHit(int x, int y);

protected:
	virtual void OnClick() = 0;
};