#pragma once
#include "QtWidgets/QtWidgets"

class MainWindow : public QMainWindow {
   public:
    // constructor
    explicit MainWindow(QWidget* parent = nullptr);

   private:
    // setup UI
    void setupUI();

   private:
    QLineEdit* num1LineEdit_;   // line edit for number 1
    QLineEdit* num2LineEdit_;   // line edit for number 2
    QLineEdit* answerLineEdit_; // line edit for answer
    QPushButton* calcButton_;   // calculation button
};
