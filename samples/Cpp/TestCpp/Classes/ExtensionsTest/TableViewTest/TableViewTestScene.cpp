#include "TableViewTestScene.h"
#include "CustomTableViewCell.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

void runTableViewTest()
{
	Scene *pScene = Scene::create();
	TableViewTestLayer *pLayer = TableViewTestLayer::create();
	pScene->addChild(pLayer);
	Director::getInstance()->replaceScene(pScene);
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size winSize = Director::getInstance()->getWinSize();

    TableView* tableView = TableView::create(this, Size(250, 60));
    tableView->setDirection(kScrollViewDirectionHorizontal);
    tableView->setPosition(Point(20,winSize.height/2-30));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();

	tableView = TableView::create(this, Size(60, 250));
	tableView->setDirection(kScrollViewDirectionVertical);
	tableView->setPosition(Point(winSize.width-150,winSize.height/2-120));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();

	// Back Menu
	MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(TableViewTestLayer::toExtensionsMainLayer, this));
	itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
	Menu *menuBack = Menu::create(itemBack, NULL);
	menuBack->setPosition(Point::ZERO);
	addChild(menuBack);

    return true;
}

void TableViewTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}

void TableViewTestLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

Size TableViewTestLayer::tableCellSizeForIndex(TableView *table, unsigned int idx)
{
    if (idx == 2) {
        return Size(100, 100);
    }
    return Size(60, 60);
}

TableViewCell* TableViewTestLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    String *string = String::createWithFormat("%d", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        Sprite *sprite = Sprite::create("Images/Icon.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point(0, 0));
        cell->addChild(sprite);

        LabelTTF *label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(Point::ZERO);
		label->setAnchorPoint(Point::ZERO);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        LabelTTF *label = (LabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }


    return cell;
}

unsigned int TableViewTestLayer::numberOfCellsInTableView(TableView *table)
{
    return 20;
}
