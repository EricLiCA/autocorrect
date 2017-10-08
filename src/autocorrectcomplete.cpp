#include "autocorrectcomplete.h"
#include "ui_autocorrectcomplete.h"

AutoCorrectComplete::AutoCorrectComplete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoCorrectComplete)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(click()), this, SLOT(back()));
    tree_ = nullptr;
}

AutoCorrectComplete::~AutoCorrectComplete()
{
    delete ui;
}

void AutoCorrectComplete::on_pushButton_clicked()
{
    back();
}

void AutoCorrectComplete::back()
{
    this->hide();
}

void AutoCorrectComplete::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.endsWith(" ")){     //autocorrect
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

        else{ // autocomplete if only one letter typed by the user
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

    else if(arg1 != ""){    // autocomplete
        ui->textEdit->clear();
        std::string word = arg1.toStdString();
        tree_->autocomplete(word);

        std::vector<std::string> lexiconV = tree_->getSuggestions();

        for(int i = 0; i < lexiconV.size() && i < 10; i++){
            std::string word = lexiconV[i];
            QString w = QString::fromStdString(word);
            ui->textEdit->append(w);
        }
    }

    else
        ui->textEdit->clear();
}

void AutoCorrectComplete::setTree(Tree* tree){
    tree_ = tree;
}
