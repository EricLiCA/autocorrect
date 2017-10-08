#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <QWidget>
#include "tree.h"

namespace Ui {
class Autocomplete;
}

class Autocomplete : public QWidget
{
    Q_OBJECT

public:
    explicit Autocomplete(QWidget *parent = 0);
    ~Autocomplete();
    void setTree(Tree* tree);

public slots:
    void back();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Autocomplete *ui;
    Tree* tree_;

};

#endif // AUTOCOMPLETE_H
