#include "mainwindow.h"
#include "ui_mainwindow.h"


QStandardItemModel *model;
int bykSayi = 0;
void FilledTable() // Txt belgesini oku veri varsa Table içerisine aktar.
{
    QFile dosya("newFile.txt");
    if (!dosya.exists()) // dosya kontrol
    {
        QMessageBox::warning(nullptr,"Hata","Dosya Bulunamadı!");
    }
    else {
    dosya.open(QFile::ReadOnly);
    QTextStream txt(&dosya);
    QList<QStandardItem *> row;
    while (!txt.atEnd())
    {
        QString line=txt.readLine();
        QStringList dizi = line.split(' ');
        row.append(new QStandardItem(dizi[0]));
        row.append(new QStandardItem(dizi[1]));
        row.append(new QStandardItem(dizi[2]));
        row.append(new QStandardItem(dizi[3]));
        row.append(new QStandardItem(dizi[4]));
        model->appendRow(row);
        row.clear();
        if (bykSayi < dizi[0].toInt()){
            bykSayi = dizi[0].toInt();
        }
    }
    dosya.close();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0,5, this); // Tableview için model oluşturma
    model ->setHeaderData(0,Qt::Horizontal, QObject::tr("No")); // model başlıklarını ayarla
    model ->setHeaderData(1,Qt::Horizontal, QObject::tr("İsim"));
    model ->setHeaderData(2,Qt::Horizontal, QObject::tr("Soyisim"));
    model ->setHeaderData(3,Qt::Horizontal, QObject::tr("Telefon"));
    model ->setHeaderData(4,Qt::Horizontal, QObject::tr("E-Posta"));

    ui->tableView->setModel(model);
    FilledTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFile dosya ("newFile.txt");
    if(!dosya.exists())
    {
        QMessageBox::warning(this,"Hata","Dosya Bulunamadı!! Yeni Dosya Oluşturuluyor..");
        dosya.setFileName("newFile.txt");
        dosya.open(QFile::WriteOnly);
        dosya.close();
    }
    dosya.open(QFile::WriteOnly);
    QTextStream text(&dosya);
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            QModelIndex index = model->index(i,0);
            QString data = model->data(index).toString();
            index = model->index(i,1);
            QString data1 =model->data(index).toString();
            index = model->index(i,2);
            QString data2 = model->data(index).toString();
            index = model->index(i,3);
            QString data3 = model->data(index).toString();
            index =model->index(i,4);
            QString data4 = model->data(index).toString();
            QString line = data+" "+data1+" "+data2+" "+data3+" "+data4+" ";
            text << line +"\n";
            j=model->columnCount();
        }
    }
    dosya.close();
    QMessageBox::information(this,"Başarılı","Tablo Dosyaya Kayıt Edildi!");
}
void MainWindow::on_pushButton_2_clicked()
{
    QString Ad = ui ->textEdit->toPlainText();
    QString Soyad = ui->textEdit_2->toPlainText();
    QString Tel = ui ->textEdit_3->toPlainText();
    QString Eposta =ui->textEdit_4->toPlainText();
    QList<QStandardItem *> row;
    row.append(new QStandardItem(QString("%1").arg(bykSayi+1)));
    row.append(new QStandardItem(Ad));
    row.append(new QStandardItem(Soyad));
    row.append(new QStandardItem(Tel));
    row.append(new QStandardItem(Eposta));
    model->appendRow(row);
    bykSayi +=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    for (int i = selected.count()-1; i>=0; --i) {
        model->removeRow(selected.at(i).row());
    }
}
int id = 0;
void MainWindow::on_pushButton_4_clicked()
{
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            QModelIndex index = model->index(i,j);
            if (model->data(index) == id)
            {
                model->setData(model->index(i,1), ui->textEdit->toPlainText());
                model->setData(model->index(i,2), ui->textEdit_2->toPlainText());
                model->setData(model->index(i,3), ui->textEdit_3->toPlainText());
                model->setData(model->index(i,4), ui->textEdit_4->toPlainText());
                break;
            }
        }
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    int selectedRow = selected.first().row();
    int column = 0;
    QModelIndex ind = model->index(selectedRow,column);
    id = model->data(ind).toInt();
}
