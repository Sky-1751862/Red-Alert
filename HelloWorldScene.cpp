#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"Construction.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ͼ������ͼƬ���߱�����2��n���ݣ�128x128
	auto bg = Sprite::create("BackgroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	//��ͼ������������ˮƽ�ظ�ƽ�̣���ֱ�ظ�ƽ��
	Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	bg->getTexture()->setTexParameters(tp);
	bg->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg, 0);



	Sprite* boxA = Sprite::create("new_154__0.png");
	boxA->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(-120, 120));
	addChild(boxA, 10, kBoxA_Tag);
	boxA->setScale(0.1);

	Sprite* boxB = Sprite::create("new_181__0.png");
	boxB->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(boxB, 20, kBoxB_Tag);
	boxB->setScale(0.1);

	Sprite* boxC = Sprite::create("SM_jianzhu_04__0.png");
	boxC->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(120, 160));
	addChild(boxC, 30, kBoxC_Tag);
	boxC->setScale(0.1);


	return true;
}
void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");

	// ����һ���¼������� OneByOne Ϊ���㴥��
	auto listener = EventListenerTouchOneByOne::create();
	// �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
	listener->setSwallowTouches(true);

	// ʹ�� lambda ʵ�� onTouchBegan �¼��ص�����
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		// ��ȡ�¼����󶨵� target 
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		// ��ȡ��ǰ�����������԰�ť��λ������
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		// �����Χ�жϼ��
		if (rect.containsPoint(locationInNode))
		{
			log("sprite x = %f, y = %f ", locationInNode.x, locationInNode.y);
			log("sprite tag = %d", target->getTag());
			target->runAction(ScaleBy::create(0.06f, 1.06f));
			return true;
		}
		return false;
	};

	// �����ƶ�ʱ����
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// �ƶ���ǰ��ť���������λ��
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	// ����¼���������
	listener->onTouchEnded = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded.. ");

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// �����Χ�жϼ��
		if (rect.containsPoint(locationInNode))
		{
			log("sprite x = %f, y = %f ", locationInNode.x, locationInNode.y);
			log("sprite tag = %d", target->getTag());
			target->runAction(ScaleTo::create(0.2f, 0.2f));
		}
	};

	// ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(kBoxA_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(kBoxB_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(kBoxC_Tag));
}

void HelloWorld::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}