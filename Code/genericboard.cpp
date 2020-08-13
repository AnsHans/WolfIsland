#include "genericboard.h"

GenericBoard::GenericBoard(QWidget *parent, short BoardSize) :
    QFrame(parent), size(BoardSize)
{
    board = new GenericCell*[BoardSize];
    for(int i = 0; i < BoardSize ; i++){
        board[i] = new GenericCell[BoardSize];
    }
    Animal::setStaticMembers(BoardSize, this);
    emitForWidgets();
    setFocusPolicy(Qt::StrongFocus);
}

GenericBoard::~GenericBoard()
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j].clear();
        }
    }
    for(int i = 0; i < size; i++){
        delete[] board[i];
    }
    delete[] board;
}

/*-----------------------------------SIMULATUON LOGIC------------------------------------------*/

void GenericBoard::oneRound()
{
 //Each timer event generates a newRound.
 this->moveAll();
 this->calibrate();
 this->relations();
 this->cleanUp();
 this->emitForWidgets();
}

void GenericBoard::moveAll(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j].moveAll();
        }
    }
}

void GenericBoard::calibrate()
{

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Animal* oneAnimal = nullptr;
            int size_of_vector = board[i][j].content.size();
            for(int k = 0; k < size_of_vector; k++){
                oneAnimal = board[i][j].content.at(k);
                board[oneAnimal->getX()][oneAnimal->getY()].add(oneAnimal);
                if (oneAnimal->isType("Bunny") && oneAnimal != nullptr) board[i][j].rabbits--;
                else if (oneAnimal->isType("Wolf_m") && oneAnimal != nullptr) board[i][j].males--;
                else if (oneAnimal->isType("Wolf_f") && oneAnimal != nullptr) board[i][j].females--;
            }
            for(int k = 0; k < size_of_vector; k++){
                board[i][j].content.erase(board[i][j].content.begin());

            }
        }
    }
}

void GenericBoard::relations()
{

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){

           for(Animal* oneAnimal : board[i][j].content){
               if(dynamic_cast<Wolf_m*>(oneAnimal) != nullptr){
                        Wolf_m* wolf;
                        wolf = dynamic_cast<Wolf_m*>(oneAnimal);
                        if(wolf->getBodyFat() <= 0){
                              killMe(wolf,wolf->getX(),wolf->getY());
                        }
                        else oneAnimal->relation();
               }

              else if(dynamic_cast<Wolf_f*>(oneAnimal) != nullptr){
                   Wolf_f* wolf;
                   wolf = dynamic_cast<Wolf_f*>(oneAnimal);
                   if(wolf->getBodyFat() <= 0){
                       killMe(wolf,wolf->getX(),wolf->getY());
                   }
                   else oneAnimal->relation();
                }

               else if(oneAnimal != nullptr)oneAnimal->relation();
           }
        }
        }
}

void GenericBoard::emitForWidgets()
{
    //UpdateWolves Num and Rabbits
    /******* DODAJ DO WOLF _ M *********/
    int Wolves = 0;
    int Bunnies = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Wolves = Wolves + board[i][j].males;
            Wolves = Wolves + board[i][j].females;
            Bunnies = Bunnies + board[i][j].rabbits;
        }
    }
    emit GenericBoard::numWolvesChanged(Wolves);
    emit GenericBoard::numBunniesChanged(Bunnies);
}

void GenericBoard::clear()
{
    if(timer.isActive() == true) timer.stop();
    for(int i = 0; i < size ; i++){
        for(int j = 0; j <size; j++){
            board[i][j].clear();
        }
    }
    isStarted = false;
    emitForWidgets();
    update();
}

void GenericBoard::add(Animal *AnimalToPut, short x, short y)
{
    board[x][y].content.push_back(AnimalToPut);
    if (AnimalToPut->isType("Bunny") && AnimalToPut != nullptr) board[x][y].rabbits++;
    else if (AnimalToPut->isType("Wolf_m") && AnimalToPut != nullptr) board[x][y].males++;
    else if (AnimalToPut->isType("Wolf_f") && AnimalToPut != nullptr) board[x][y].females++;

}

bool GenericBoard::isThereBunny(short x, short y)
{
    return this->board[x][y].isThereBunny();

}

bool GenericBoard::isThereWolf_f(short x, short y)
{
    return this->board[x][y].isThereWolf_f();
}

void GenericBoard::killMe(Animal* AnimalToKill, short x, short y)
{
    if (AnimalToKill->isType("Bunny") && AnimalToKill != nullptr) board[x][y].rabbits--;
    else if (AnimalToKill->isType("Wolf_m") && AnimalToKill != nullptr) board[x][y].males--;
    else if (AnimalToKill->isType("Wolf_f") && AnimalToKill != nullptr) board[x][y].females--;

    for(int i = 0; i < board[x][y].content.size(); i++){
        if(AnimalToKill == board[x][y].content.at(i)) {
            delete AnimalToKill;
            board[x][y].content.at(i) = nullptr;
    }
}
}

/*-----------------------------------GUI SECTION OF THE SOURCE CODE------------------------------------------*/
QSize GenericBoard::sizeHint() const
{
    return QSize(size * 50 + frameWidth() * 2,
                 size * 50 + frameWidth() * 2);
    //W tej funkcji definiujemy rekomendowany rozmiar,
}

QSize GenericBoard::minimumSizeHint() const
{
    return QSize(size * 35 + frameWidth() * 2,
                 size * 35 + frameWidth() * 2);
}

void GenericBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);


    QPainter painter(this);
    QRect rect = contentsRect();
    for(int Xl = 0; Xl < size; Xl++){
        for(int Yl = 0; Yl < size; Yl++){
            drawSquare(painter, rect.left() + Xl * squareWidth(),
                       rect.top() + Yl * squareHeight());
        }

    }


}

void GenericBoard::timerEvent(QTimerEvent *event){
    oneRound();
    QFrame::timerEvent(event);
    update();
}

void GenericBoard::mousePressEvent(QMouseEvent *event)
{
    if(isPaused == true || isStarted == false){
    if(key == "Q"){
    int x = event->x();
    int y = event->y();
    x = x/squareWidth();
    y = y/squareHeight();

    bool safety = board[x][y].getSafety();
    for(Animal* oneAnimal : board[x][y].content){
        if(dynamic_cast<Wolf_m*>(oneAnimal) != nullptr){
        delete oneAnimal;
        oneAnimal = nullptr;
        }
        else if(dynamic_cast<Wolf_f*>(oneAnimal) != nullptr){
            delete oneAnimal;
            oneAnimal = nullptr;
        }
    }
    board[x][y].content.clear();
    board[x][y].males = 0;
    board[x][y].females = 0;
    board[x][y].setSafety(!safety);
    update();
    }
    else if(key == "M"){
        int x = event->x();
        int y = event->y();
        x = x/squareWidth();
        y = y/squareHeight();
        if(board[x][y].getSafety() == true){
            Wolf_m* newAnimal = new Wolf_m(x,y);
            board[x][y].add(newAnimal);
        }
        emitForWidgets();
        update();
    }
    else if(key == "F"){
        int x = event->x();
        int y = event->y();
        x = x/squareWidth();
        y = y/squareHeight();
        if(board[x][y].getSafety() == true){
            Wolf_f* newAnimal = new Wolf_f(x,y);
            board[x][y].add(newAnimal);
        }
        emitForWidgets();
        update();
    }
    else if(key == "R"){
        int x = event->x();
        int y = event->y();
        x = x/squareWidth();
        y = y/squareHeight();
        Bunny* newAnimal = new Bunny(x,y);
        board[x][y].add(newAnimal);
        emitForWidgets();
        update();
    }
}
}

void GenericBoard::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == 'Q' || event->key() == 'M' || event->key() == 'F' || event->key() == 'R') key = event->key();
}
void GenericBoard::drawSquare(QPainter &painter, int x, int y)
{
    if(board[x / squareWidth()][y / squareHeight()].getSafety() == false){
        QColor color1 = QColor(50,150,100);
        int Width = squareWidth() - 2;
        int Height = (squareHeight() - 2);

        QRect text1_rect(x + 1, y + 1, Width, Height);

        painter.fillRect(text1_rect,color1);

        QString text1("R: ");
        text1.append(QString::number(board[x/squareWidth()][y/squareHeight()].rabbits));
        painter.drawText(text1_rect,text1);

        painter.setPen(color1.lighter());
            painter.drawLine(x, y + squareHeight() - 1, x, y);
            painter.drawLine(x, y, x + squareWidth() - 1, y);

            painter.setPen(color1.darker());
            painter.drawLine(x + 1, y + squareHeight() - 1,
                             x + squareWidth() - 1, y + squareHeight() - 1);
            painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                             x + squareWidth() - 1, y + 1);
    }
    else{
    QColor color1 = QColor(244,164,96);
    QColor color2 = QColor(70,130,180);
    QColor color3 = QColor(199,21,133);
    int Width = squareWidth() - 2;
    int Height = (squareHeight() - 2) / 3;
    //Podziel na części
    QRect text1_rect(x + 1, y + 1, Width, Height);
    QRect text2_rect(x + 1, y + 1 + Height, Width, Height);
    QRect text3_rect(x + 1, y + 1 + 2*Height, Width, Height);

    painter.fillRect(text1_rect,color1);
    painter.fillRect(text2_rect,color2);
    painter.fillRect(text3_rect,color3);

    QString text1("R: ");
    text1.append(QString::number(board[x/squareWidth()][y/squareHeight()].rabbits));
    QString text2("M: ");
    text2.append(QString::number(board[x/squareWidth()][y/squareHeight()].males));
    QString text3("F: ");
    text3.append(QString::number(board[x/squareWidth()][y/squareHeight()].females));
    painter.drawText(text1_rect,text1);
    painter.drawText(text2_rect,text2);
    painter.drawText(text3_rect,text3);

    painter.setPen(color1.lighter());
        painter.drawLine(x, y + squareHeight() - 1, x, y);
        painter.drawLine(x, y, x + squareWidth() - 1, y);

        painter.setPen(color1.darker());
        painter.drawLine(x + 1, y + squareHeight() - 1,
                         x + squareWidth() - 1, y + squareHeight() - 1);
        painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                         x + squareWidth() - 1, y + 1);
   }
}

void GenericBoard::start()
{
    //zresetuj wszystkie warości
    if(isStarted == false){
    timer.start(1000, this);
    isStarted = true;
    isPaused = false;
    }
    else {
        if(isPaused == false){
            timer.stop();
            isPaused = true;
        }
        else{
        isPaused = false;
        timer.start(100, this);
        }
    }
}

void GenericBoard::resize(int BoardSize)
{
    BoardSize = 30;
    isStarted = false;
    isPaused = false;
    this->timer.stop();
    board = new GenericCell*[this->size];
    for(int i = 0; i < size ; i++){
        delete[] board[i];
    }
    delete[] board;

    board = new GenericCell*[BoardSize];
    for(int i = 0; i < BoardSize ; i++){
        board[i] = new GenericCell[BoardSize];
    }
    Animal::setStaticMembers(BoardSize, this);
    Animal* zwierzak;
    for(int i = 0; i < 3; i++){
     zwierzak = new Bunny(2,2);
     board[0][0].add(zwierzak);
    }

    for(int i = 0; i < 2; i++){
        zwierzak = new Wolf_f(2,2);
        board[0][0].add(zwierzak);
    }
    for(int i = 0; i < 2; i++){
        zwierzak = new Wolf_m(2,2);
        board[0][0].add(zwierzak);
    }
    this->size = BoardSize;
    emitForWidgets();
    this->timer.stop();
}

void GenericBoard::cleanUp(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int vector_size = board[i][j].content.size();
            for(int k = 0; k < vector_size; k++){
                if(board[i][j].content.at(k) == nullptr){
                    board[i][j].content.erase(board[i][j].content.begin() + k);
                    k--;
                    vector_size--;
                }
            }
        }
    }
}



