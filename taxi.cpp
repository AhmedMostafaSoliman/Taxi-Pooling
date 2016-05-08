#include "taxi.h"
#include <QDebug>

Taxi::Taxi(int x,int y)
{
    this->x=x;
    this->y=y;
    occupied=0;
    customerLocationx=customerLocationy=customerDestinationx=customerDestinationy=-1;
}

void Taxi::move()
{
    if(!path.empty())
    {
        char dir=path.top();
        path.pop();
        std::vector<std::vector<cell*>> *cells=Grid::getgrid();
        if(dir== 'r')
        {
            (*cells)[x][y]->setState(cell :: Road);
            y++;
            (*cells)[x][y]->setState(cell :: Taxi);
        }
        else if(dir == 'l')
        {
            (*cells)[x][y]->setState(cell :: Road);
            y--;
            (*cells)[x][y]->setState(cell :: Taxi);

        }
        else if(dir == 'u')
        {
            (*cells)[x][y]->setState(cell :: Road);
            x--;
            (*cells)[x][y]->setState(cell :: Taxi);


        }
        else if(dir == 'd')
        {
            (*cells)[x][y]->setState(cell :: Road);
            x++;
            (*cells)[x][y]->setState(cell :: Taxi);
        }
        else if(dir=='x')
        {
            //find path to destination2
            //if()
            path=findPath(customerDestinationx,customerDestinationy);
            (*cells)[customerLocationx][customerLocationy]->setState(cell :: Pavement);
        }
    }
    else
    {
        customerLocationx=customerLocationy=customerDestinationx=customerDestinationy=-1;
        occupied=0;
    }
}

std::stack<char> Taxi::findPath(int desx,int desy)
{
   std::stack<char> taxi_path;
   std::vector<std::vector<cell*>>* g=Grid::getgrid();
   std::vector<std::vector<cell*>> v=*g;
   int numRows=v.size();
   int numCols=v[0].size();
   std::vector<std::vector<char>>par(numRows,std::vector<char>(numCols,'s'));
   std::vector<std::vector<bool>>vis(numRows,std::vector<bool>(numCols));

   std::queue<std::pair<int,int>>q;
   q.push(std::make_pair(this->x,this->y));

   while(!q.empty())
   {
       int curx = q.front().first,cury=q.front().second; q.pop();
       vis[curx][cury]=1;
       //qDebug()<<"curx"<<curx<<"cury"<<cury;

       /*   r
        * r p r
        *   r
        */
       if((abs(curx-desx)+abs(cury-desy))==1)
       {
           //qDebug()<<"done";
           while(!q.empty())
               q.pop();

           if(customerLocationx==-1 ||customerLocationy==-1)
                taxi_path.push('x'); // a char that is used to delay the taxi for a moment when reaching the
                                        //customer for the first time
           while(par[curx][cury] != 's')
           {
               if(par[curx][cury]=='u')
               {
                  curx++;
                  taxi_path.push('u');
               }
               else if(par[curx][cury]=='d')
               {
                  curx--;
                  taxi_path.push('d');
               }
               else if (par[curx][cury]=='l')
               {
                    cury++;
                    taxi_path.push('l');
               }
               else if(par[curx][cury]=='r')
               {
                    cury--;
                    taxi_path.push('r');
               }
            }
           return taxi_path;
        }

       if(curx+1 <numRows)
       {
           if(!vis[curx+1][cury] && v[curx+1][cury]->isRoad()){
               q.push(std::make_pair(curx+1,cury)); par[curx+1][cury]='d';
           }
       }
       if(curx-1 >=0)
       {
           if(!vis[curx-1][cury] && v[curx-1][cury]->isRoad()){
               q.push(std::make_pair(curx-1,cury)); par[curx-1][cury]='u';
           }
       }
       if(cury+1 <numCols)
       {
           if(!vis[curx][cury+1] && v[curx][cury+1]->isRoad()){
               q.push(std::make_pair(curx,cury+1));par[curx][cury+1]='r';
           }
       }
       if(cury-1 >=0)
       {
           if(!vis[curx][cury-1] && v[curx][cury-1]->isRoad()){
               q.push(std::make_pair(curx,cury-1));par[curx][cury-1]='l';
           }
       }

    }
}

void Taxi::setPath(std::stack<char> p)
{
    path=p;
    occupied=1;
}

int Taxi::getx()
{
    return x;
}

int Taxi::gety()
{
    return y;
}

void Taxi::setx(int x)
{
    this->x=x;
}

void Taxi::sety(int y)
{
    this->y=y;
}


void Taxi::setCustomer(int curx,int cury,int desx,int desy)
{
    customerLocationx=curx;
    customerLocationy=cury;
    customerDestinationx=desx;
    customerDestinationy=desy;
}

bool Taxi::isOccupied()
{
    return occupied;
}

