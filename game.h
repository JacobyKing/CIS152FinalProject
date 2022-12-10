#ifndef GAME_H
#define GAME_H

#include <QDate>

class Game
{
private:
    QString name;
    QString genre;
    QDate releaseDate;
    double price;
public:
    Game();
    Game(QString name, QString genre, QDate releaseDate, double price);
    QString getName();
    void setName(QString name);
    QString getGenre();
    void setGenre(QString genre);
    QDate getReleaseDate();
    void setReleaseDate(QDate releaseDate);
    double getPrice();
    void setPrice(double price);

    QString printReleaseDate();
    QString getGameInfo();
};

#endif // GAME_H
