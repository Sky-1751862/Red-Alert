#include "Construction.h"


Construction* Construction::createConstruction(Point position, cons_type construction_type)
{
	Construction* construction = Construction::create();
	if (construction)
	{
		construction->initConstruction(position,construction_type);
		return construction;
	}
	CC_SAFE_DELETE(construction);
	return NULL;
}
void Construction::initConstruction(Point position, cons_type construction_type)
{

	switch (construction_type)
	{
	case(power):
	  {
		  character = Sprite::create("power.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money=100;
	  } break;
	case(miner):
	  {
		character = Sprite::create("miner.png");
		  hp = 500;
		  produce_power = 0;
		  cost_power = 50;
		  cost_money = 100;
 	  }break;
	case(base):
	  {
		  character = Sprite::create("base.png");
		  hp = 500;
		  produce_power = 200;
	  	  cost_power = 0;
		  cost_money = 100;
	  }break;
	case(armycamp):
	  {
		  character = Sprite::create("armycamp.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money = 100;
	  }break;
	case(tankfac):
	  {
		  character = Sprite::create("tankfac.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money = 100;
	  }break;
	}

	attackers = std::list<Soldier*>();


	character->setScale(1.5);
	character->setPosition(position);
	this->addChild(character);//��ѡ��״̬ͼ

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Construction::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//�����¼�������

	this->scheduleUpdate();//��ʱ����״̬
	this->schedule(schedule_selector(Construction::updateattack), 1.0f, kRepeatForever, 0);//ִ�й���������ˢ��
}

void Construction::update(float dt)
{
	
}//����״̬


void Construction::push_back_attacker(Soldier*attack)
{
	attackers.push_back(attack);
}//���ӹ�����
void Construction::updateattack(float dt)
{
	for (attacker = attackers.begin(); attacker != attackers.end(); attacker++)
	{
		hp -= (*attacker)->atk;
	}
}//ִ�й�������


bool Construction::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 4 &&
		point.x<position.x + character->getContentSize().width / 4 &&
		point.y>position.y - character->getContentSize().height / 4 &&
		point.y < position.y + character->getContentSize().height / 4
		);      //�ı�״̬���������ѡ��ָ��
	return false;

}