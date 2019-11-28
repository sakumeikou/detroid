#include "KeyInput.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

USING_NS_CC;
	
void KeyInput::Init(Node * node)
{
	for (int keyCode = 0; keyCode < static_cast<int>(EventKeyboard::KeyCode::KEY_PLAY); keyCode++)
	{
		inputType.insert(std::make_pair(CHAR(KEYCODE(keyCode)), INPUT_TRG::OFF));
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		
		if (!nowInputType.insert(std::make_pair(CHAR(keyCode), 1)).second)
		{
			nowInputType[CHAR(keyCode)] = 1;
		}
		
		inputType[CHAR(keyCode)] = INPUT_TRG::ON_MOM;
		
		return true;
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)->bool
	{

		nowInputType[CHAR(keyCode)] = 0;

		inputType[CHAR(keyCode)] = INPUT_TRG::OFF_MOM;

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
	
	for (auto trgType : nowInputType)
	{
		// oldKeyとNowKeyの入力状態が違っていたときに中に入る
		if (oldInputType[trgType.first] != nowInputType[trgType.first])
		{
			// 押した瞬間,離した瞬間の情報を押し続ける、離し続けるに変える
			if (inputType[CHAR(trgType.first)] == INPUT_TRG::ON_MOM)
			{
				inputType[CHAR(trgType.first)] = INPUT_TRG::ON;
			}
			else if (inputType[CHAR(trgType.first)] == INPUT_TRG::OFF_MOM)
			{
				inputType[CHAR(trgType.first)] = INPUT_TRG::OFF;
			}
			else
			{
				// 上記のどちらでもなかった場合は何もしない
			}
		}

		if (oldInputType.insert(std::make_pair(CHAR(trgType.first),nowInputType[trgType.first])).second)
		{
			oldInputType[trgType.first] = nowInputType[trgType.first];
		}
	}
}
