#include "genericboard.h"

GenericBoard::GenericBoard(QWidget *parent, short BoardSize) :
    QFrame(parent), size(BoardSize)
{
    board = new GenericCell*[BoardSize];
    for(int i = 0; i < BoardSize ; i++){
        board[i] = new GenericCell[BoardSize];
    }
    Animal::setStaticMembers(BoardSize, this);
    Animal* zwierzak;
    for(int i = 0; i < 2; i++){
     zwierzak = new Bunny(2,2);
     board[2][2].add(zwierzak);
    }
    for(int i = 0; i < 3; i++){
        zwierzak = new Wolf_f(2,3);
        board[2][3].add(zwierzak);
    }
}

/*-----------------------------------SIMULATUON LOGIC------------------------------------------*/

void GenericBoard::oneRound()
{
 //Each timer event generates a newRound.
 this->moveAll();
 this->calibrate();
 this->relations();
}

void GenericBoard::clear()
{
    for(int i = 0; i < size ; i++){
        for(int j = 0; j <size; j++){
            board[i][j].clear();
        }
    }
    isStarted = false;
    update();
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
            int size_of_vector = board[i][j].content.size();
            int k = 1;
            for(Animal* oneAnimal : board[i][j].content){
               int x = oneAnimal->getX();
               int y = oneAnimal->getY();
               board[x][y].add(oneAnimal);
               board[i][j].content.erase(board[i][j].content.begin());
               k++;
               if(k > size_of_vector) break; // W ten sposób unikam nieskończonej pętli
            }
        }
    }
}

void GenericBoard::relations()
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           int size_of_vector = board[i][j].content.size();
           int k = 1;
           for(Animal* oneAnimal : board[i][j].content){
               oneAnimal->relation();
               k++;
               if(k > size_of_vector) break;
           }
        }
    }
}

void GenericBoard::add(Animal *AnimalToPut, short x, short y)
{
    board[x][y].content.push_back(AnimalToPut);
}

bool GenericBoard::isThereBunny(short x, short y)
{
    return this->board[x][y].isThereBunny();
}

bool GenericBoard::isThereWolf_f(short x, short y)
{
    return this->board[x][y].isThereWolf_f();
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
void GenericBoard::drawSquare(QPainter &painter, int x, int y)
{
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

void GenericBoard::start()
{
    //zresetuj wszystkie warości
    if(isStarted == false){
    timer.start(100, this);
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


