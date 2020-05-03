#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_prixBienImmobilier_valueChanged(int);
    void on_apport_valueChanged(int);
    void on_fraisDossiers_valueChanged(int);
    void on_dureePret_valueChanged(int);
    void on_assurancePret_valueChanged(int);
    void on_tauxInteret_valueChanged(double);
    void on_logementNeuf_clicked(bool);
    void on_logementAncien_clicked(bool);

private:
    void update();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
