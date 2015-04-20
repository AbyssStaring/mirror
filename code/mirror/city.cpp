#include "city.h"

city::city(RoleInfo *roleInfo, MapItem *bag_item)
: myTabFrame(NULL), myRole(roleInfo), m_bag_item(bag_item)
{
	ui.setupUi(this);

	m_drugs = new shop(0, myRole, m_bag_item);
	ui.tabWidget->addTab(m_drugs, QString::fromLocal8Bit("药店"));

	m_variety = new shop(1, myRole, m_bag_item);
	ui.tabWidget->addTab(m_variety, QString::fromLocal8Bit("杂货铺"));

	m_smithy = new smithy(myRole);
	ui.tabWidget->addTab(m_smithy, QString::fromLocal8Bit("铁匠铺"));
	tabChanged(0);

	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
}

city::~city()
{
	delete m_drugs;
	delete m_smithy;
}

void city::updateRoleInfo(void)
{

}

void city::tabChanged(int index)
{
	QString iconPath = ":/city/Resources/city/";
	iconPath += QString::number(index + 1) + ".png";
	ui.lbl_img->setPixmap(QPixmap(iconPath));

	QString strInfo[10] = {
		QString::fromLocal8Bit("妙手回春"),
		QString::fromLocal8Bit("包罗万象"),
		QString::fromLocal8Bit("装备强化"),
		QString::fromLocal8Bit("转生")
	};
	ui.edit_display->setText(strInfo[index]);
}