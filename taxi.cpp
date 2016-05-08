#include "taxi.h"
#include <QDebug>

Taxi::Taxi(int x,int y)
{
    this->x=x;
    this->y=y;
    occupied=0;
    customerLocationx=customerLocationy=customerDestinationx=customerDestinationy=-1;
    orientation='l';
}

void Taxi::move()
{
    std::vector<std::vector<cell*>> *cells=Grid::getgrid();
    if(!path.empty())
    {
        char dir=path.top();
        path.pop();
        if(dir== 'r')
        {
            (*cells)[x][y]->setState(cell :: Road);
            y++;
            if(customerDestinationx!=-1)
                (*cells)[x][y]->setState(cell :: ReservedTaxi);
            else if(occupied)
                (*cells)[x][y]->setState(cell :: OccupiedTaxi);
            else
                (*cells)[x][y]->setState(cell :: VacantTaxi);

            (*cells)[x][y]->rotateLabel(true);
            (*cells)[x][y]->rotateLabel(true);
        }
        else if(dir == 'l')
        {
            (*cells)[x][y]->setState(cell :: Road);
            y--;
            if(customerDestinationx!=-1)
                (*cells)[x][y]->setState(cell :: ReservedTaxi);
            else if(occupied)
                (*cells)[x][y]->setState(cell :: OccupiedTaxi);
            else
                (*cells)[x][y]->setState(cell :: VacantTaxi);
        }
        else if(dir == 'u')
        {
            (*cells)[x][y]->setState(cell :: Road);
            x--;
            if(customerDestinationx!=-1)
                (*cells)[x][y]->setState(cell :: ReservedTaxi);
            else if(occupied)
                (*cells)[x][y]->setState(cell :: OccupiedTaxi);
            else
                (*cells)[x][y]->setState(cell :: VacantTaxi);

            (*cells)[x][y]->rotateLabel(false);
        }
        else if(dir == 'd')
        {
            (*cells)[x][y]->setState(cell :: Road);
            x++;
            if(customerDestinationx!=-1)
                (*cells)[x][y]->setState(cell :: ReservedTaxi);
            else if(occupied)
                (*cells)[x][y]->setState(cell :: OccupiedTaxi);
            else
                (*cells)[x][y]->setState(cell :: VacantTaxi);

            (*cells)[x][y]->rotateLabel(true);
        }
        else if(dir=='x')
        {
            path=findPath(customerDestinationx,customerDestinationy);
            (*cells)[customerLocationx][customerLocationy]->setState(cell :: Pavement);
            (*cells)[x][y]->setState(cell :: OccupiedTaxi);
            if(orientation=='r')
            {
                (*cells)[x][y]->rotateLabel(true);
                (*cells)[x][y]->rotateLabel(true);
            }
            else if(orientation=='d')
            {
                (*cells)[x][y]->rotateLabel(true);
            }
            else if(orientation=='u')
            {
                (*cells)[x][y]->rotateLabel(false);
            }
            customerLocationx=customerLocationy=customerDestinationx=customerDestinationy=-1;
            occupied=1;
        }
        orientation=dir;
    }
    else
    {
        if(occupied)
        {
            occupied=0;
            (*cells)[x][y]->setState(cell :: VacantTaxi);
            if(orientation=='r')
            {
                (*cells)[x][y]->rotateLabel(true);
                (*cells)[x][y]->rotateLabel(true);
            }
            else if(orientation=='d')
            {
                (*cells)[x][y]->rotateLabel(true);
            }
            else if(orientation=='u')
            {
                (*cells)[x][y]->rotateLabel(false);
            }
        }
    }
}

std::stack<char> Taxi::findPath(int desx,int desy)
{
   std::stack<char> taxi_path;
   std::vector<std::vector<cell*>> v=*Grid::getgrid();
   int numRows=v.size();
   int numCols=v[0].size();

   std::vector<std::vector<char>>par(numRows,std::vector<char>(numCols,'s'));
   par[x][y]='T';

   std::queue<std::pair<int,int>>BFS_Q;
   BFS_Q.push(std::make_pair(this->x,this->y));

   while(!BFS_Q.empty())
   {
       int curx = BFS_Q.front().first,cury=BFS_Q.front().second; BFS_Q.pop();
       if((abs(curx-desx)+abs(cury-desy))==1)
       {
           while(!BFS_Q.empty())
               BFS_Q.pop();

           if(customerLocationx==-1 ||customerLocationy==-1)
                taxi_path.push('x'); // a char that is used to delay the taxi for a moment when reaching the
                                        //customer for the first time
           while(par[curx][cury] != 'T')
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
           if(par[curx+1][cury]=='s' && v[curx+1][cury]->isRoad()){
               BFS_Q.push(std::make_pair(curx+1,cury)); par[curx+1][cury]='d';
           }
       }
       if(curx-1 >=0)
       {
           if(par[curx-1][cury]=='s' && v[curx-1][cury]->isRoad()){
               BFS_Q.push(std::make_pair(curx-1,cury)); par[curx-1][cury]='u';
           }
       }
       if(cury+1 <numCols)
       {
           if(par[curx][cury+1]=='s' && v[curx][cury+1]->isRoad()){
               BFS_Q.push(std::make_pair(curx,cury+1));par[curx][cury+1]='r';
           }
       }
       if(cury-1 >=0)
       {
           if(par[curx][cury-1]=='s' && v[curx][cury-1]->isRoad()){
               BFS_Q.push(std::make_pair(curx,cury-1));par[curx][cury-1]='l';
           }
       }

    }
   return std::stack<char>();
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

