#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QFile file;
    globPath = QFileDialog::getOpenFileName(nullptr,"","C:\\Users\\koroc\\Documents\\","*.json");
    file.setFileName(globPath);
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        file.close();
    }


    ui->jsonDocumentTextEdit->clear();      // Очищаем текстовое поле в случае перезапуска


    ui->jsonDocumentTextEdit->setColumnCount(2); // Указываем число колонок
    ui->jsonDocumentTextEdit->setShowGrid(true); // Включаем сетку

    // Устанавливаем заголовки колонок
    QStringList headers;
        headers.append("key");
        headers.append("value");

    ui->jsonDocumentTextEdit->setHorizontalHeaderLabels(headers);
    // сетка
    ui->jsonDocumentTextEdit->horizontalHeader()->setStretchLastSection(true);

    for(int i=0; i<doc.object().length(); i++){
        ui->jsonDocumentTextEdit->insertRow(i);
        ui->jsonDocumentTextEdit->setItem(i,0, new QTableWidgetItem(doc.object().keys()[i]));
        ui->jsonDocumentTextEdit->setItem(i,1, new QTableWidgetItem(doc.object().value(doc.object().keys()[i]).toString()));
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    // С помощью диалогового окна получаем имя файла с абсолютным путём
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
    // Создаём объект файла и открываем его на запись
    QFile file(saveFileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

//  В obj запишем все данные с таблицы на текущий момент: уже что-то успели изменить"
    QJsonObject obj;

    for(int i=0; i<doc.object().length(); i++){
        QString key;
        QTableWidgetItem *item_key = ui->jsonDocumentTextEdit->item(i,0);

        QString value;
        QTableWidgetItem *item_value = ui->jsonDocumentTextEdit->item(i,1);


        if ((NULL != item_key) && (NULL != item_value))  {
           key = item_key->text();
           value = item_value->text();

           obj[key] = value;
        }
    }

    doc.setObject(obj);
    // Записываем текущий объект Json в файл
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();   // Закрываем файл
}

