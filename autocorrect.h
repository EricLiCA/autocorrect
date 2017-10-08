#ifndef AUTOCORRECT_H
#define AUTOCORRECT_H

#include <QWidget>
#include "tree.h"

namespace Ui {
class Autocorrect;
}

class Autocorrect : public QWidget
{
    Q_OBJECT

public:
    explicit Autocorrect(QWidget *parent = 0);
    ~Autocorrect();
    void setTree(Tree* tree);

public slots:
    void back();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Autocorrect *ui;
    Tree* tree_;
};

#endif // AUTOCORRECT_H
