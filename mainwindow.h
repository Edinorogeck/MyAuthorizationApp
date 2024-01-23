#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Для SQL
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

// Для графиков
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include <QPieSeries>
#include <QPieSlice>

#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void openPage2();
    QSqlDatabase db;

    QStackedWidget *stackedWidget;

    // графики
    QChartView *chartViewBar;
    QChartView *chartViewPie;
    QChartView *chartViewLine;
protected:
    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
