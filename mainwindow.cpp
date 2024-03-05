#include "mainwindow.h"
#include <QGridLayout>
#include <QStringList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    list = new QListWidget(this);
    list->setSortingEnabled(true);
    list->setEditTriggers(QAbstractItemView::DoubleClicked);

    buttonAdd = new QPushButton("&Add book");
    buttonDelete = new QPushButton("&Delete book");
    book = new QLineEdit();

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(book, 0, 0);
    layout->addWidget(buttonAdd, 0, 1);
    layout->addWidget(list, 1, 0);
    layout->addWidget(buttonDelete, 1, 1);

    this->setLayout(layout);
    this->setWindowTitle("Book titles");

    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(addBook()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(deleteBook()));
    connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editBook()));
    connect(list, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(checkDuplicate(QListWidgetItem*)));
    //connect(list, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT());

    book->setFocus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addBook()
{
    QString b = book->text();
    QList<QListWidgetItem *> exists = list->findItems(b, Qt::MatchFixedString);
    if (exists.size()==0 and b.length()>0)
    {
        new QListWidgetItem(book->text(), list);
    }
    else if (exists.size()>0)
    {
        QMessageBox::warning(this, "Error", "Book title already exists", 0, 1);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Book title is blank", 0, 1);
    }
    book->clear();
    book->setFocus();
}

void MainWindow::deleteBook()
{
    int answer = QMessageBox::question(this, "Delete", "Are you sure?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (answer == QMessageBox::Yes)
    {
        int row = list->currentRow();
        QListWidgetItem *removed = list->takeItem(row);
        delete removed;
    }
}

void MainWindow::editBook()
{
    QListWidgetItem *item = list->currentItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    list->editItem(item);
}

void MainWindow::checkDuplicate(QListWidgetItem *item)
{
    QList<QListWidgetItem *> exists = list->findItems(item->text(), Qt::MatchFixedString);
    if (exists.size()>1)
    {
        int row = list->currentRow();
        QListWidgetItem *removed = list->takeItem(row);
        delete removed;
    }
}
