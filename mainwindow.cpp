#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    tree_ = nullptr;
    ui->setupUi(this);
    connect(ui->autocompleteMode, SIGNAL(click()), this, SLOT(openAutocompleteWindow()));
    connect(ui->autocorrectMode, SIGNAL(click()), this, SLOT(openAutocorrectWindow()));
    connect(ui->autoMode, SIGNAL(click()), this, SLOT(openAutocorrectcompleteWindow()));
    connect(ui->pushButton, SIGNAL(click()), this, SLOT(loadLexicon()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAutocompleteWindow()
{
    if(tree_ != nullptr){
        autocompleteW = new Autocomplete();
        autocompleteW->setTree(tree_);      // autocompleteW has the same tree as MainWindow
        autocompleteW->show();
    }
    else
        ui->textEdit->setPlainText("Upload lexicon before using autocomplete mode!");
}

void MainWindow::openAutocorrectWindow()
{
    if(tree_ != nullptr){
        autocorrectW = new Autocorrect();
        autocorrectW->setTree(tree_);      // autocompleteW has the same tree as MainWindow
        autocorrectW->show();
    }
    else
        ui->textEdit->setPlainText("Upload lexicon before using autocorrect mode!");
}

void MainWindow::openAutocorrectcompleteWindow()
{
    if(tree_ != nullptr){
        autocorrectcompleteW = new AutoCorrectComplete();
        autocorrectcompleteW->setTree(tree_);      // autocompleteW has the same tree as MainWindow
        autocorrectcompleteW->show();
    }
    else
        ui->textEdit->setPlainText("Upload lexicon before using autocomplete/correct mode!");
}

void MainWindow::on_autocompleteMode_clicked()
{
    openAutocompleteWindow();
}

void MainWindow::on_autocorrectMode_clicked()
{
    openAutocorrectWindow();
}

void MainWindow::on_autoMode_clicked()
{
    openAutocorrectcompleteWindow();
}

void MainWindow::on_pushButton_clicked()
{
    loadLexicon();
}

void MainWindow::loadLexicon()
{
    // get lexicon path from file browser
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File Explorer"), "", tr("(*.txt);;All Files (*)"));
    std::string lexiconFile = fileName.toStdString();

    if(fileName.isEmpty()){
        ui->textEdit->setPlainText("File is empty!");
        return;
    }
    else{
        tree_ = new Tree(lexiconFile);
        std::vector<std::string> lexiconV = tree_->getLexique();
        ui->textEdit->setPlainText("Loaded lexicon succesfully from file: " + fileName);

    }
}

