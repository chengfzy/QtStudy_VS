#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

class Eg16_SqlBasic : public QMainWindow
{
	Q_OBJECT

public:
	Eg16_SqlBasic(QWidget *parent = Q_NULLPTR);

private:
	void createDbUseSqlQuery();					//create data and table, using sql query
	bool connectDb(const QString& dbName);		//connect database

	void selectUseSqlTableModel();				//select data use QSqlTableModel

	void showDataView();						//show data view

private:
	QPushButton* m_pSqlQueryButton;
	QPushButton* m_pSqlTableModelButton;
};
