#include <QtCore/QtCore>
#include <QImage>

void testEquip(const QString &inFile)
{
	qDebug() << __FUNCTION__ << inFile;

	QFile file(inFile);
	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}

	QImage img;
	quint32 ID, ac1, ac2, mac1, mac2, dc1, dc2, mc1, mc2, sc1, sc2, need, needLvl, price;
	QString name, msg, strImgPath;

	QDataStream out(file.readAll());
	while (!out.atEnd())
	{
		out >> ID >> name >> img >> ac1 >> ac2 >> mac1 >> mac2 
			>> dc1 >> dc2 >> mc1 >> mc2 >> sc1 >> sc2 >> need >> needLvl >> price >> msg;

		qDebug() << ID << name << ac1 << ac2 << mac1 << mac2
		         << dc1 << dc2 << mc1 << mc2 << sc1 << sc2 << need << needLvl << price << msg;
	}

	file.close();
}

void Equip(const QString &inFile, const QString &outFile)
{
	qDebug() << __FUNCTION__ << inFile << outFile;

	QFile Rfile(inFile);
	if (!Rfile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "open " << inFile << "error.";
		return;
	}

	QFile Wfile(outFile);
	if (!Wfile.open(QIODevice::WriteOnly))
	{
		qDebug() << "open " << outFile << "error.";
		return;
	}

	QString strTmp;
	QStringList list;
	int i = 0;
	QImage img;
	quint32 ID, photo, ac1, ac2, mac1, mac2, dc1, dc2, mc1, mc2, sc1, sc2, need, needLvl, price;
	QString name, msg, strImgPath;

	QDataStream iData(&Wfile);

	Rfile.readLine(1000);		//��һ���Ǳ���
	while (!Rfile.atEnd())
	{
		strTmp = Rfile.readLine(1000);
		if (strTmp.isEmpty() || strTmp.isNull())
		{
			//��ֹ�ļ�β���пհ��С�
			break;
		}
		list = strTmp.split("\t");
		i = 0;
		ID = list.at(i++).toUInt();
		name = list.at(i++);

		photo = list.at(i++).toUInt();
		strImgPath = QString("./Resources/equip/");
		strImgPath += QString::number(photo) + QString(".bmp");
		if (!QFile::exists(strImgPath))
		{
			strImgPath = QString("./Resources/equip/0.bmp");
		}
		img = QImage(strImgPath);
		if (img.isNull())
		{
			qDebug() << "No Head:" << strImgPath;
			break;
		}

		ac1 = list.at(i++).toUInt();
		ac2 = list.at(i++).toUInt();
		mac1 = list.at(i++).toUInt();
		mac2 = list.at(i++).toUInt();
		dc1 = list.at(i++).toUInt();
		dc2 = list.at(i++).toUInt();
		mc1 = list.at(i++).toUInt();
		mc2 = list.at(i++).toUInt();
		sc1 = list.at(i++).toUInt();
		sc2 = list.at(i++).toUInt();
		need = list.at(i++).toUInt();
		needLvl = list.at(i++).toUInt();
		price = list.at(i++).toUInt();
		msg = list.at(i++);
		
		iData << ID << name << img << ac1 << ac2 << mac1 << mac2;
		iData << dc1 << dc2 << mc1 << mc2 << sc1 << sc2 << need << needLvl << price << msg;
	}

	Rfile.close();
	Wfile.close();

	qDebug() << __FUNCTION__ << "run over";

	testEquip(outFile);
}