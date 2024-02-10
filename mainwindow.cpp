#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <string>

double tmp=0;
std::string lastOperation;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->plus, &QPushButton::clicked, this, &MainWindow::plus);
    connect(ui->result_num, &QPushButton::clicked, this, &MainWindow::diaplayResult);
    connect(ui->one, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->two, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->three, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->four, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->five, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->six, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->seven, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->eight, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->nine, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->null_num, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->point, &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->minus, &QPushButton::clicked, this, &MainWindow::subtraction);
    connect(ui->multiply, &QPushButton::clicked, this, &MainWindow::multiply);
    connect(ui->devide, &QPushButton::clicked, this, &MainWindow::devide);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::numberButtonClicked() {
    if (ui->one_input->isEnabled()){
        ui->one_input->setFocus();
    }
    if (ui->two_input->isEnabled()){
        ui->two_input->setFocus();
    }

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonText = button->text();
        QLineEdit *activeInput = qobject_cast<QLineEdit*>(focusWidget());

        if (activeInput) {
            int cursorPos = activeInput->cursorPosition();
            activeInput->insert(buttonText);
            activeInput->setCursorPosition(cursorPos + 1);
        }
    }
}

void MainWindow::performOperation() {
    bool ok;
    QString text;

    if (ui->one_input->isEnabled()) {
        text = ui->one_input->text();
    } else if (ui->two_input->isEnabled()) {
        text = ui->two_input->text();
    }

    double number = text.toDouble(&ok);
    if (ok) {
        if (ui->one_input->isEnabled()) {
            tmp = number;
            ui->one_input->setDisabled(true);
        } else if (ui->two_input->isEnabled()) {
            if (lastOperation == "plus") {
                tmp += number;
            } else if (lastOperation == "subtraction") {
                tmp -= number;
            } else if (lastOperation == "multiply") {
                tmp *= number;
            } else if (lastOperation == "devide") {
                if (number != 0) {
                    tmp /= number;
                } else {
                    ui->output->setText("ERROR");
                }
            }
            ui->one_input->setText(QString::number(tmp));
        }
        ui->two_input->clear();
        ui->two_input->setDisabled(false);
        ui->two_input->setFocus();
    } else if (!ok && !(ui->two_input->text() == "")) {
        ui->output->setText("ERROR");
    }
}

void MainWindow::plus() {
    performOperation();
    lastOperation = "plus";
}

void MainWindow::subtraction() {
    performOperation();
    lastOperation = "subtraction";
}

void MainWindow::multiply() {
    performOperation();
    lastOperation = "multiply";
}

void MainWindow::devide() {
    performOperation();
    lastOperation = "devide";
}

void MainWindow::diaplayResult() {
    bool ok;
    if (lastOperation=="plus") {
        QString textTwo = ui->two_input->text();
        double numberTwo = textTwo.toDouble(&ok);
        tmp+=numberTwo;
        ui->output->setText(QString::number(tmp));
        ui->one_input->clear();
        ui->two_input->clear();
        ui->two_input->setEnabled(false);
        ui->one_input->setEnabled(true);
        ui->one_input->setFocus();
    } else if (lastOperation=="subtraction") {
        QString textTwo = ui->two_input->text();
        double numberTwo = textTwo.toDouble(&ok);
        tmp-=numberTwo;
        ui->output->setText(QString::number(tmp));
        ui->one_input->clear();
        ui->two_input->clear();
        ui->two_input->setEnabled(false);
        ui->one_input->setEnabled(true);
        ui->one_input->setFocus();
    } else if (lastOperation=="multiply") {
        QString textTwo = ui->two_input->text();
        double numberTwo = textTwo.toDouble(&ok);
        tmp*=numberTwo;
        ui->output->setText(QString::number(tmp));
        ui->one_input->clear();
        ui->two_input->clear();
        ui->two_input->setEnabled(false);
        ui->one_input->setEnabled(true);
        ui->one_input->setFocus();
    } else if (lastOperation=="devide") {
        QString textTwo = ui->two_input->text();
        double numberTwo = textTwo.toDouble(&ok);
        if (numberTwo!=0){
            tmp /= numberTwo;
            ui->output->setText(QString::number(tmp));
        } else {
            ui->output->setText("ERROR");
        }
        ui->one_input->clear();
        ui->two_input->clear();
        ui->two_input->setEnabled(false);
        ui->one_input->setEnabled(true);
        ui->one_input->setFocus();
    } else {
        ui->output->setText("ERROR");
    }
}

void MainWindow::clear(){
    tmp=0;
    ui->one_input->clear();
    ui->two_input->clear();
    ui->output->clear();
    ui->two_input->setEnabled(false);
    ui->one_input->setEnabled(true);
    ui->one_input->setFocus();
}
