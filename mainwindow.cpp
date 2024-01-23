#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("MyTestDB");
    db.setUserName("QtUser");
    db.setPassword("QtUser");
    //db.setUserName("postgres");
    //db.setPassword("user");

    if (db.open())
    {
        qDebug() << "Connected";
    }
    else
    {
        qDebug() << "Fail";
    }

    ui->stackedWidget->setCurrentIndex(0);

    openPage2();


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Нажатие на кнопку в форме авторизации
void MainWindow::on_loginButton_clicked()
{
    QString username = ui->userInput->text();
    QString password = ui->passwordInput->text();
    qDebug() << username << password;

    QString command = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "' AND status = 0";
    QSqlQuery query(db);
    if (query.exec(command))
    {
        if (query.size() > 0)
        {
            QMessageBox::information(this, "Авторизация успешна.", "Ты успешно авторизован.");

            ui->stackedWidget->setCurrentIndex(1);
        }
        else
        {
            QMessageBox::information(this, "Ошибка авторизации.", "Попробуйте снова.");
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    chartViewBar->resize(chartViewBar->parentWidget()->size());
    chartViewPie->resize(chartViewPie->parentWidget()->size());
    chartViewLine->resize(chartViewLine->parentWidget()->size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Показываем диалоговое окно с подтверждением выхода
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Выйти?",
                                                               "Вы уверены, что хотите выйти?",
                                                               QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore(); // Игнорируем событие закрытия
    } else {
        QMessageBox::information(this, "Выход", "До скорых встреч");
        event->accept(); // Принимаем событие закрытия
    }
}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if (arg1 == 1)
    {

    }
}

void MainWindow::openPage2()
{
    //---------------Bar---------------//
    QBarSet *set0 = new QBarSet("Игорь");
    QBarSet *set1 = new QBarSet("Виктор");
    QBarSet *set2 = new QBarSet("Ольга");
    QBarSet *set3 = new QBarSet("Мария");
    QBarSet *set4 = new QBarSet("Павел");

    *set0 << 10 << 20 << 30 << 40 << 50 << 60;
    *set1 << 50 << 70 << 40 << 45 << 80 << 70;
    *set2 << 30 << 50 << 80 << 13 << 80 << 50;
    *set3 << 50 << 60 << 70 << 30 << 40 << 25;
    *set4 << 90 << 70 << 50 << 30 << 16 << 42;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Успеваемость студентов");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chartViewBar = new QChartView(chart);
    chartViewBar->setParent(ui->chart1);
    //---------------------------------//

    //---------------Pie---------------//
    QPieSeries *pieSeries = new QPieSeries();
    pieSeries->append("Игорь", 10);
    pieSeries->append("Виктор", 20);
    pieSeries->append("Ольга", 30);
    pieSeries->append("Мария", 40);
    pieSeries->append("Павел", 50);

    QPieSlice *pieSlice = pieSeries->slices().at(1);
    pieSlice->setExploded();
    pieSlice->setLabelVisible();
    pieSlice->setPen(QPen(Qt::darkGreen, 2));
    pieSlice->setBrush(Qt::green);

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Успеваемость студентов");
    pieChart->setAnimationOptions(QChart::SeriesAnimations);

    chartViewPie = new QChartView(pieChart);
    chartViewPie->setParent(ui->chart2);
    //---------------------------------//

    //---------------Line--------------//
    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->append(0, 6);
    seriesLine->append(2, 4);
    seriesLine->append(3, 8);
    seriesLine->append(7, 4);
    seriesLine->append(10, 5);
    seriesLine->append(11, 10);
    seriesLine->append(13, 3);
    seriesLine->append(17, 6);
    seriesLine->append(18, 3);
    seriesLine->append(20, 2);

    QChart *ChartLine = new QChart();
    ChartLine->addSeries(seriesLine);
    ChartLine->createDefaultAxes();
    ChartLine->setTitle("Успеваемость студентов");
    ChartLine->setAnimationOptions(QChart::SeriesAnimations);


    chartViewLine = new QChartView(ChartLine);
    chartViewLine->setRenderHint(QPainter::Antialiasing);
    chartViewLine->setParent(ui->chart3);
    //---------------------------------//
}

