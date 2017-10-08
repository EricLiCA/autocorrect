#include "autocomplete.h"
#include "ui_autocomplete.h"


Autocomplete::Autocomplete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Autocomplete)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(click()), this, SLOT(back()));
    tree_ = nullptr;
}

Autocomplete::~Autocomplete()
{
    delete ui;
}

void Autocomplete::on_pushButton_clicked()
{
    back();
}

void Autocomplete::back()
{
    this->hide();
}

void Autocomplete::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1 != ""){
        ui->textEdit->clear();
        std::string word = arg1.toStdString();
        tree_->autocomplete(word);
        std::vector<std::string> lexiconV = tree_->getSuggestions();

        for(int i = 0; i < lexiconV.size() && i < 10; i++){
            std::string word = lexiconV[i];
            QString w = QString::fromStdString(word);
            ui->textEdit->append(w); // output suggestions to ui
        }
    }

    else
        ui->textEdit->clear();
}

void Autocomplete::setTree(Tree* tree){
    tree_ = tree;
}
