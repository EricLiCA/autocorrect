#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "autocomplete.h"
#include "autocorrect.h"
#include "autocorrectcomplete.h"
#include "tree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadLexicon();

public slots:
    void openAutocompleteWindow();
    void openAutocorrectWindow();
    void openAutocorrectcompleteWindow();

private slots:
    void on_autocompleteMode_clicked();

    void on_autocorrectMode_clicked();

    void on_autoMode_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFile* lexicon;
    Tree* tree_;
    Autocomplete* autocompleteW;
    Autocorrect* autocorrectW;
    AutoCorrectComplete* autocorrectcompleteW;

};

#endif // MAINWINDOW_H
