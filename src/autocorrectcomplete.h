#ifndef AUTOCORRECTCOMPLETE_H
#define AUTOCORRECTCOMPLETE_H

#include <QWidget>
#include "tree.h"

namespace Ui {
class AutoCorrectComplete;
}

class AutoCorrectComplete : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCorrectComplete(QWidget *parent = 0);
    ~AutoCorrectComplete();
    void setTree(Tree* tree);

public slots:
    void back();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::AutoCorrectComplete *ui;
    Tree* tree_;
};

#endif // AUTOCORRECTCOMPLETE_H
