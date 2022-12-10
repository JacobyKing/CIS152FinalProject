#include "widget.h"
#include "ui_widget.h"

//Helper functions

//Used to sort the gameInfoVec by price
bool compareGamePrice(Game firstGame, Game nextGame){
    return(firstGame.getPrice() < nextGame.getPrice());
}

//Used to sort the gameInfoVec by release date
bool compareGameReleaseDate(Game firstGame, Game nextGame){
    return(firstGame.getReleaseDate() < nextGame.getReleaseDate());
}

//Used to sort the gameInfoVec by genre
bool compareGameGenre(Game firstGame, Game nextGame){
    return(firstGame.getGenre() < nextGame.getGenre());
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Setting the size of the widget and setting the current page to the start page
    this->setFixedSize(1200, 1000);
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    //Initializing a regular expression validatior for game name input box
    QRegExp rx("^([a-zA-Z0-9,:]{1,6}\\s?([a-zA-Z0-9,: ]{1,24})?)");
    QValidator * validator = new QRegExpValidator(rx, this);
    ui->gameNameInputBox2->setValidator(validator);
    //Making the table read only
    ui->gameTableWidget4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Setting resize modes of each column in the table
    ui->gameTableWidget4->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->gameTableWidget4->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->gameTableWidget4->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->gameTableWidget4->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
}

Widget::~Widget()
{
    delete ui;
}

//Sets the current widget to the game name input page
void Widget::setGameNameInputPage()
{
    ui->stackedWidget->setCurrentWidget(ui->gameNameInputPage);
    this->setFixedSize(1100, 600);
    //If not running for the first time, hide the 'Done' button on the gameNameInputPage so that you can only add for one game
    if(!firstRun){
        ui->toGameInfoInputPageButton2->hide();
    }
}

//Sets the current widget to the game info input page
void Widget::setGameInfoInputPage()
{
    //If this is the first run, it should check if the gameNameList is empty, if not it should set the gameInfoInputPage and start the first iteration of the setNextVecInput() function
    if(firstRun){
        if(!gameNameList.empty()){
            ui->stackedWidget->setCurrentWidget(ui->gameInfoInputPage);
            this->setFixedSize(1200, 1000);
            setNextVecInput();
            ui->popularGenreLabel3->setText("Popular " + ui->genreInput3->currentText() + " Games:");
            ui->genreDescriptionLabel3->setText("Minecraft, Grand Theft Auto, The Sims");
        }
        //If this is the first run and the gameNameList is not empty, it should display an error message
        else{
            ui->errorLabel2->setText("Your List Must Have at Least One Game");
        }
    }
    //If this is not the first run, set the gameInfoInputPage and make the gameNameLabel display the game the user wants to add to the table
    else{
        ui->stackedWidget->setCurrentWidget(ui->gameInfoInputPage);
        this->setFixedSize(1200, 1000);
        ui->gameNameLabel3->setText(addedGame);
    }
}

//Sets the current widget to tableDisplayPage, also calls the setTable method to use the current values in the gameInfoVec to create a table
void Widget::setTableDisplayPage()
{
    ui->stackedWidget->setCurrentWidget(ui->tableDisplayPage);
    this->setFixedSize(1800, 1000);
    setTable();
}

//If the gameNameInputBox has acceptable input, according to regex, and it is the first run, add the game to the gameNameList
void Widget::pushGameNameInput()
{
    if(ui->gameNameInputBox2->hasAcceptableInput()){
        if(firstRun){
            gameNameList.push_back(ui->gameNameInputBox2->text());
        }
        //If the gameNameInputBox has acceptable input, accoring to regex, and it is not the first run, set the addedGame variable equal to the input game and immediately go to the gameInfoInputPage to input the data for that game
        else{
            addedGame = ui->gameNameInputBox2->text();
            setGameInfoInputPage();
        }
        //If the gameNameInputBox has acceptable input, clear the errorLabel from any previous errors
        ui->errorLabel2->setText("");
    }
    //If the gameNameInputBox does not have acceptable input, set the errorLabel accordingly
    else{
        ui->errorLabel2->setText("Invalid Entry");
    }
    //Whether the value in the gameNameInputBox is valid or not, clear it
    ui->gameNameInputBox2->setText("");
}

//Adds the input from gameInfoInputPage to gameInfoVec
void Widget::pushVecInput()
{
    gameInfoVec.push_back(Game(ui->gameNameLabel3->text(), ui->genreInput3->currentText(), ui->releaseDateInput3->date(), ui->priceInput3->value()));
}

//Resets fields and title of gameInfoInputPage until the end of gameNameList, then goes to the tableDisplayPage
void Widget::setNextVecInput()
{
    static auto itr = gameNameList.begin();
    if(firstRun){
        if(itr != gameNameList.end()){
            ui->gameNameLabel3->setText(*itr);
            itr++;
        }
        else{
            //Sets firstRun to false so that the original gameNameList will no longer be used on the gameNameInputPage and gameInfoInputPage because only one game will be added at a time from here
            firstRun = false;
            setTableDisplayPage();
        }
    }
    //If this is not the first run, sets the tableDisplayPage since pushVecInput() method has already been called for the one game that the user is trying to add
    else{
        setTableDisplayPage();
    }
    //Clear all of the input fields for future entries
    ui->releaseDateInput3->setDate(QDate(2000, 1, 1));
    ui->priceInput3->setValue(0.00);
    ui->genreInput3->setCurrentIndex(0);
}

//Calls the correct sort function on the gameInfoVec based on the sortSelection field
void Widget::sortVector()
{
    if(ui->sortSelection4->currentText() == "Genre"){
        sort(gameInfoVec.begin(), gameInfoVec.end(), compareGameGenre);
    }
    else if(ui->sortSelection4->currentText() == "Release Date"){
        sort(gameInfoVec.begin(), gameInfoVec.end(), compareGameReleaseDate);
    }
    else if(ui->sortSelection4->currentText() == "Price"){
        sort(gameInfoVec.begin(), gameInfoVec.end(), compareGamePrice);
    }
}

//Uses the current items in the gameInfoVec to set the gameTableWidget, also sets the rowIndexBox maximum to the size of the gameInfoVec
void Widget::setTable()
{
    ui->gameTableWidget4->setRowCount(0);
    ui->rowIndexBox4->setMaximum(gameInfoVec.size());
    for(auto i : gameInfoVec){
        //Creating a new row and inserting stored data into each column for each game in the gameInfoVec
        ui->gameTableWidget4->insertRow(ui->gameTableWidget4->rowCount());
        ui->gameTableWidget4->setItem((ui->gameTableWidget4->rowCount() - 1), 0, new QTableWidgetItem(i.getName()));
        ui->gameTableWidget4->setItem((ui->gameTableWidget4->rowCount() - 1), 1, new QTableWidgetItem(i.getGenre()));
        ui->gameTableWidget4->setItem((ui->gameTableWidget4->rowCount() - 1), 2, new QTableWidgetItem(i.printReleaseDate()));
        ui->gameTableWidget4->setItem((ui->gameTableWidget4->rowCount() - 1), 3, new QTableWidgetItem("$" + QString::number(i.getPrice())));
    }
}

//'Start' button on startPage, calls the setGameNameInputPage() method
void Widget::on_toGameNameInputPageButton1_clicked()
{
    setGameNameInputPage();
}

//'Add' button on gameNameInputPage, calls the pushGameNameInput() method
void Widget::on_gameNameInputButton2_clicked()
{
    pushGameNameInput();
}

//If the enter key is pressed while the gameNameInputBox is selected, calls the pushGameNameInput() method
void Widget::on_gameNameInputBox2_returnPressed()
{
    pushGameNameInput();
}

//When the text in the gameNameInputBox is changed, automatically capitalizes the first letter of each word
void Widget::on_gameNameInputBox2_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
        //If the first character in the gameNameInputBox is a lowercase letter, capitalize it
        if(arg1.begin()->isLetter() && arg1.begin()->isLower()){
            ui->gameNameInputBox2->setText(arg1.begin()->toUpper());
        }
        //Else if the last input character in the gameNameInputBox is a lowercase letter with a space behind it, capitalize it
        else if(arg1.back().isLetter() && arg1.back().isLower()){
            if(arg1.at(arg1.lastIndexOf(arg1.back()) - 1) == " "){
                ui->gameNameInputBox2->setText(arg1.chopped(1) + arg1.back().toUpper());
            }
        }
    }
}

//'Done' button on gameNameInputPage, calls the setGameInfoInputPage() method
void Widget::on_toGameInfoInputPageButton2_clicked()
{
    setGameInfoInputPage();
}

//As the genreInput box is changed, displays popular games of that genre to the user
void Widget::on_genreInput3_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Sandbox"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Minecraft, Grand Theft Auto, The Sims");
    }
    else if(arg1 == "Real-Time Strategy"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Civilization 6, Stellaris, StarCraft");
    }
    else if(arg1 == "Shooter"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Halo, Gears of War, DOOM");
    }
    else if(arg1 == "MOBA"){
        ui->popularGenreLabel3->setText("Popular Multiplayer Online Battle Arena Games:");
        ui->genreDescriptionLabel3->setText("League of Legends, Dota 2, Overwatch");
    }
    else if(arg1 == "Role-Playing"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Fallout 4, God of War, Spider-Man: Miles Morales");
    }
    else if(arg1 == "Simulation & Sports"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Forza Motorsport, EA Sports UFC, NBA 2K");
    }
    else if(arg1 == "Puzzle & Party Games"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Jackbox Party Pack, Portal 2, Super Smash Bros. Ultimate");
    }
    else if(arg1 == "Action-Adventure"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Star Wars Jedi: Fallen Order, Ghosts of Tsushima, Elden Ring");
    }
    else if(arg1 == "Survival & Horror"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("The Long Dark, The Forest, Resident Evil");
    }
    else if(arg1 == "Platformer"){
        ui->popularGenreLabel3->setText("Popular " + arg1 + " Games:");
        ui->genreDescriptionLabel3->setText("Cuphead, Super Mario Galaxy, Crash Bandicoot");
    }
}

//'Enter' button on gameInfoInputPage, calls pushVecInput() and setNextVecInput() methods to add the current input to the gameInfoVec and either prepare the gameInfoInputPage for another entry or go to the tableDisplayPage
void Widget::on_gameInfoInputButton3_clicked()
{
    pushVecInput();
    setNextVecInput();
}

//'Sort' button on tableDisplayPage, calls the sortVector() and setTable() methods to use the requested sort function on the gameInfoVec and redisplays it on the gameTableWidget
void Widget::on_sortButton4_clicked()
{
    sortVector();
    setTable();
}

//'Delete Row' button on tableDisplayPage, deletes the requested game index from the gameInfoVec and redisplays it on the gameTableWidget
void Widget::on_rowDeleteButton4_clicked()
{
    if(gameInfoVec.size() > 1){
        gameInfoVec.erase(gameInfoVec.begin() + (ui->rowIndexBox4->value() - 1));
        setTable();
    }
}

//'Add' button on the tableDisplayPage, calls the setGameNameInputPage() method with the firstRun variable set as false so that only one game can be input at a time
void Widget::on_addGameButton4_clicked()
{
    setGameNameInputPage();
}
