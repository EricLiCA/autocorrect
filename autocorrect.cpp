#include "autocorrect.h"
#include "ui_autocorrect.h"

Autocorrect::Autocorrect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Autocorrect)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(click()), this, SLOT(back()));
    tree_ = nullptr;
}

Autocorrect::~Autocorrect()
{
    delete ui;
}

void Autocorrect::on_pushButton_clicked()
{
    back();
}

void Autocorrect::back()
{
    this->hide();
}

void Autocorrect::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.endsWith(" ")){
        ui->textEdit->clear();
        std::string word = arg1.toStdString();
        word.pop_back();

        if(word.size() > 1){
            std::vector<std::string> lexiconV = tree_->autocorrect(word);
            for(int i = 0; i < lexiconV.size() && i < 10; i++){
                std::string word = lexiconV[i];
                QString w = QString::fromStdString(word);
                ui->textEdit->append(w);
            }
        }

        else{ // if use only types one letter, suggests words
            ui->textEdit->clear();
            std::string word = arg1.toStdString();
            word.pop_back();
            tree_->autocomplete(word);

            std::vector<std::string> lexiconV = tree_->getSuggestions();

            for(int i = 0; i < lexiconV.size() && i < 10; i++){
                std::string word = lexiconV[i];
                QString w = QString::fromStdString(word);
                ui->textEdit->append(w);
            }
        }

    }

    else
        ui->textEdit->clear();
}

void Autocorrect::setTree(Tree* tree){
    tree_ = tree;
}
