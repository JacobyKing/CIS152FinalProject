#ifndef WIDGET_H
#define WIDGET_H

#include "game.h"
#include <QWidget>
#include <list>
#include <iterator>
#include <QDebug>
#include <QRegExpValidator>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void setGameNameInputPage();

    void setGameInfoInputPage();

    void setTableDisplayPage();

    void pushGameNameInput();

    void pushVecInput();

    void setNextVecInput();

    void sortVector();

    void setTable();

private slots:
    void on_toGameNameInputPageButton1_clicked();

    void on_gameNameInputButton2_clicked();

    void on_gameNameInputBox2_returnPressed();

    void on_gameNameInputBox2_textChanged(const QString &arg1);

    void on_toGameInfoInputPageButton2_clicked();

    void on_genreInput3_currentTextChanged(const QString &arg1);

    void on_gameInfoInputButton3_clicked();

    void on_sortButton4_clicked();

    void on_rowDeleteButton4_clicked();

    void on_addGameButton4_clicked();

private:
    Ui::Widget *ui;
    std::list<QString> gameNameList;
    std::vector<Game> gameInfoVec;
    bool firstRun = true;
    QString addedGame;
};
#endif // WIDGET_H
