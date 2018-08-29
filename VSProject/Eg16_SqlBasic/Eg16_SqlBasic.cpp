#include "Eg16_SqlBasic.h"
#include <QtSql>

Eg16_SqlBasic::Eg16_SqlBasic(QWidget *parent)
	: QMainWindow(parent)
{
	if (connectDb("training.db"))
	{
		QSqlTableModel* model = new QSqlTableModel;
		model->setTable("student");
		model->setSort(1, Qt::AscendingOrder);
		model->setHeaderData(1, Qt::Horizontal, "Name");
		model->setHeaderData(2, Qt::Horizontal, "Age");
		model->select();

		QTableView* view = new QTableView();
		view->setModel(model);
		view->setSelectionMode(QAbstractItemView::SingleSelection);
		view->setSelectionBehavior(QAbstractItemView::SelectRows);
		view->setColumnHidden(0, true);
		view->resizeColumnsToContents();
		view->setEditTriggers(QAbstractItemView::NoEditTriggers);

		QHeaderView* header = view->horizontalHeader();
		header->setStretchLastSection(true);

		view->show();
	}

	m_pSqlQueryButton = new QPushButton("SQL Query");
	connect(m_pSqlQueryButton, &QPushButton::clicked, this, &Eg16_SqlBasic::createDbUseSqlQuery);

	m_pSqlTableModelButton = new QPushButton("SqlTableModel");
	connect(m_pSqlTableModelButton, &QPushButton::clicked, this, &Eg16_SqlBasic::selectUseSqlTableModel);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_pSqlQueryButton);
	mainLayout->addWidget(m_pSqlTableModelButton);

	QWidget* mainWidget = new QWidget();
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
}

void Eg16_SqlBasic::createDbUseSqlQuery()
{
	//create table
	if (connectDb("training.db"))
	{
		QSqlQuery query;
		if (!query.exec("CREATE TABLE student("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"name VARCHAR, "
			"age INT)"))
		{
			QMessageBox::critical(nullptr, tr("Database Error"), query.lastError().text());
			return;
		}
	}
	else
		return;

	//insert data
	if (connectDb("training.db"))
	{
		QSqlQuery query;
		query.prepare("INSERT INTO student (name, age) VALUES(:name, :age)");
		QVariantList names;
		names << "Tom" << "Jack" << "Jane" << "Jerry";
		query.bindValue(":name", names);
		QVariantList ages;
		ages << 20 << 23 << 22 << 25;
		query.bindValue(":age", ages);
		if (!query.execBatch())
		{
			QMessageBox::critical(nullptr, tr("Database Error"), query.lastError().text());
		}

		query.finish();
		query.exec("SELECT name, age FROM student");
		while (query.next())
		{
			QString name = query.value(0).toString();
			int age = query.value(1).toInt();
			qDebug() << name << ": " << age;
		}
	}
}

bool Eg16_SqlBasic::connectDb(const QString & dbName)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setHostName("host");
	//db.setDatabaseName("dbname");
	//db.setUserName("username");
	//db.setPassword("password");
	db.setDatabaseName(dbName);

	if (!db.open())
	{
		QMessageBox::critical(nullptr, tr("Database Error!"), db.lastError().text());
		return false;
	}
	
	return true;
}

void Eg16_SqlBasic::selectUseSqlTableModel()
{
	if (connectDb("training.db"))
	{
		QSqlTableModel model;
		model.setTable("student");
		model.setFilter("age > 20 and age < 25");
		if (model.select())
		{
			for (int i = 0; i < model.rowCount(); ++i)
			{
				QSqlRecord record = model.record(i);
				QString name = record.value("name").toString();
				int age = record.value("age").toInt();
				qDebug() << name << ": " << age;
			}
		}
	}
	else
		return;
}

void Eg16_SqlBasic::showDataView()
{
	
}
