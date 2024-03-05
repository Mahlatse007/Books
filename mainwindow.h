#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>


class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addBook();
    void deleteBook();
    void editBook();
    void checkDuplicate(QListWidgetItem *item);

private:
    QListWidget *list;
    QPushButton *buttonAdd;
    QPushButton *buttonDelete;
    QLineEdit *book;
};

#endif // MAINWINDOW_H
