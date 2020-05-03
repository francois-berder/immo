#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QtDebug>

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

void MainWindow::on_prixBienImmobilier_valueChanged(int)
{
    update();
}

void MainWindow::on_apport_valueChanged(int)
{
    update();
}

void MainWindow::on_fraisDossiers_valueChanged(int)
{
    update();
}

void MainWindow::on_dureePret_valueChanged(int)
{
    update();
}

void MainWindow::on_assurancePret_valueChanged(int)
{
    update();
}

void MainWindow::on_tauxInteret_valueChanged(double)
{
    update();
}

void MainWindow::on_logementNeuf_clicked(bool)
{
    update();
}

void MainWindow::on_logementAncien_clicked(bool)
{
    update();
}

void MainWindow::update()
{
    /* Get input */
    double prixBienImmobilier = ui->prixBienImmobilier->value();
    double apport = ui->apport->value();

    /* Droits de mutation */
    double droitsMutation;
    if (ui->logementNeuf->isChecked()) {
        ui->tauxDroitsMutation->setText("0%");
        droitsMutation = 0;
    } else {
        ui->tauxDroitsMutation->setText("5.8%");
        droitsMutation = (prixBienImmobilier * 5.8) / 100.0;
    }
    ui->droitsMutation->setNum(droitsMutation);

    /* Pret a faire ? */
    if (apport <= prixBienImmobilier + droitsMutation) {
        double pret = prixBienImmobilier + droitsMutation + ui->assurancePret->value() + ui->fraisDossiers->value() - apport;
        double dureeRemboursementPret = ui->dureePret->value();
        double tauxPret = ui->tauxInteret->value();
        double tauxPretMensuel = pow(1.0 + tauxPret/100, 1.0/12.0) - 1.0;
        double mensualite = pret * tauxPretMensuel * pow(1.0+tauxPretMensuel, dureeRemboursementPret);
        mensualite /= pow(1.0+tauxPretMensuel, dureeRemboursementPret) - 1.0;
        double interetsPret = mensualite * dureeRemboursementPret - pret;
        double prixTotal = prixBienImmobilier + droitsMutation + static_cast<double>(ui->fraisDossiers->value()) + static_cast<double>(ui->assurancePret->value()) + interetsPret;

        ui->interets->setNum(interetsPret);
        ui->mensualite->setNum(mensualite);
        ui->prixTotal->setNum(prixTotal);
    } else {
        double prixTotal = prixBienImmobilier + droitsMutation;
        ui->mensualite->setText(0);
        ui->interets->setNum(0);
        ui->prixTotal->setNum(prixTotal);
    }
}
