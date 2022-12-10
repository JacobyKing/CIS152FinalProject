/* Jacoby King
 * 11/08/2022
 * CIS152 Final Project
 */
#include "game.h"

//Constructors
Game::Game()
{

}

Game::Game(QString name, QString genre, QDate releaseDate, double price)
{
    setName(name);
    setGenre(genre);
    setReleaseDate(releaseDate);
    setPrice(price);
}

//Getters and setters
QString Game::getName()
{
    return name;
}

void Game::setName(QString name)
{
    this->name = name;
}

QString Game::getGenre()
{
    return genre;
}

void Game::setGenre(QString genre)
{
    this->genre = genre;
}

QDate Game::getReleaseDate()
{
    return releaseDate;
}

void Game::setReleaseDate(QDate releaseDate)
{
    this->releaseDate = releaseDate;
}

double Game::getPrice()
{
    return price;
}

void Game::setPrice(double price)
{
    this->price = price;
}

//Returns a properly formatted QString of the releaseDate
QString Game::printReleaseDate()
{
    return QString::number(releaseDate.month()) + "-" + QString::number(releaseDate.day()) + "-" + QString::number(releaseDate.year());
}
