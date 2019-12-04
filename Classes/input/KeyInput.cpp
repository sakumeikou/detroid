#include "KeyInput.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

USING_NS_CC;
	
void KeyInput::Init(Node * node)
{
	for (int keyCode = 0; keyCode < static_cast<int>(EventKeyboard::KeyCode::KEY_PLAY); keyCode++)
	{
		_inputType.insert(std::make_pair(CHAR(KEYCODE(keyCode)), INPUT_TRG::OFF));
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (!_nowInputType.insert(std::make_pair(CHAR(keyCode), 1)).second)
		{
			_nowInputType[CHAR(keyCode)] = 1;
		}
		
		_inputType[CHAR(keyCode)] = INPUT_TRG::ON_MOMENT;
		
		return true;
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)->bool
	{
		_nowInputType[CHAR(keyCode)] = 0;

		_inputType[CHAR(keyCode)] = INPUT_TRG::OFF_MOM;

		if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}

		return true;
	};

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void KeyInput::Update()
{
	for (auto trgType : _nowInputType)
	{
		// oldKeyとNowKeyの入力状態が違っていたときに中に入る
		if (_oldInputType[trgType.first] != _nowInputType[trgType.first])
		{
			// 押した瞬間,離した瞬間の情報を押し続ける、離し続けるに変える
			if (_inputType[CHAR(trgType.first)] == INPUT_TRG::ON_MOMENT)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::ON;
			}
			else if (_inputType[CHAR(trgType.first)] == INPUT_TRG::OFF_MOM)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::OFF;
			}
			else
			{
				// 上記のどちらでもなかった場合は何もしない
			}
		}

		if (_oldInputType.insert(std::make_pair(CHAR(trgType.first),_nowInputType[trgType.first])).second)
		{
			_oldInputType[trgType.first] = _nowInputType[trgType.first];
		}
	}
}
