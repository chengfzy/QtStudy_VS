#include "MainWindow.h"

// constructor
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    setMinimumSize(800, 600);
}

// setup UI
void MainWindow::setupUI() {
    // input and output
    num1LineEdit_ = new QLineEdit("10");
    num2LineEdit_ = new QLineEdit("23");
    answerLineEdit_ = new QLineEdit;

    // layout
    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(num1LineEdit_);
    inputLayout->addWidget(new QLabel("+"));
    inputLayout->addWidget(num2LineEdit_);
    inputLayout->addWidget(new QLabel("="));
    inputLayout->addWidget(answerLineEdit_);

    // calculate button
    calcButton_ = new QPushButton("Calculate");
    connect(calcButton_, &QPushButton::clicked, [&]() {
        double num1 = num1LineEdit_->text().toDouble();
        double num2 = num2LineEdit_->text().toDouble();
        answerLineEdit_->setText(QString::number(num1 + num2));
    });
    calcButton_->click();   // init for default setting

    // main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(calcButton_);

    // center widget
    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}
