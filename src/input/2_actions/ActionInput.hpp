#pragma once

enum ActionInput {
	AI_NOOP = 0,

	WALK_LEFT,
	WALK_RIGHT,
	WALK_UP,
	WALK_DOWN,

	MENU_UP,
	MENU_DOWN,
	MENU_LEFT,
	MENU_RIGHT,
	MENU_ITEM_SELECT,
	MENU_SHOW,

	QUIT
};

enum ActionInputType {
	OTHER,
	WALK,
	USE_MENU
};

