
#include "GWInterface.h"
#include <vector>
#include <iostream>

using std::vector;

class GridWorld : public GWInterface {

  public:
    GridWorld(unsigned nrows, unsigned ncols)   {
      nrow = nrows;
      ncol=ncols;
      popul=0;
      world = new District*[nrows];
      int i;
      for(i =0; i<nrows;i++)
        {
          world[i] = new District[ncols];
        }
      // your constructor code here!
    }
    ~GridWorld(){

      // your destructor code here.
      delete world;
    }

    bool birth(int row, int col, int &id){

      if(validPoints(row, col))// check the rows and columns are valid
        {
          if(deadpeople.size() != 0)// reuse the old id
            {
              id = deadpeople.back();
              deadpeople.pop_back();

              peopleArray.at(id).node=  world[row][col].pushToBack(id,row, col);

              peopleArray.at(id).alive=true;
              world[row][col].population = world[row][col].population +1;
              popul++;
              return true;
            }
          else{
            id=popul;
          }
         arrayPerson *temp = new arrayPerson(id, world[row][col].pushToBack(id,row, col),true);
          peopleArray.push_back(*temp);

          world[row][col].population = world[row][col].population +1;
          popul++;

          return true;
        }
      else{
      return false;
    }
    }

    bool death(int personID){
          if(peopleArray.at(personID).alive == true)
            {
                Doubly *temp;
                temp = peopleArray.at(personID).node;
                if(temp->prev==temp)
                  {
                    world[peopleArray.at(personID).node->array->row][peopleArray.at(personID).node->array->col].pHead=temp->next;
                  }
                if(temp->next == nullptr)
                  {
                    world[peopleArray.at(personID).node->array->row][peopleArray.at(personID).node->array->col].pEnd= temp->prev;
                  }
                temp->prev->next=temp->next;
                world[temp->array->row][temp->array->col].population = world[temp->array->row][temp->array->col].population -1;
                peopleArray.at(personID).alive = false;
                deadpeople.push_back(personID);
                delete temp;
                popul--;
                return true;
            }
      return false;
    }

    bool whereis(int id, int &row, int &col)const{
      if(popul == 0){
        return false;
      }
      else if(peopleArray.at(id).alive==true)
        {
          row = peopleArray.at(id).node->array->row;
          col = peopleArray.at(id).node->array->col;
          return true;
        }
          return false;
    }

    bool move(int id, int targetRow, int targetCol){
          bool value = false;

          if(peopleArray.at(id).alive == true)
            {
                Doubly *temp;
                temp = peopleArray.at(id).node;
                world[temp->array->row][temp->array->col].population = world[temp->array->row][temp->array->col].population -1;
                temp->prev->next=temp->next;
                temp->array->row= targetRow;
                temp->array->col= targetCol;
                delete temp;
                value = true;
            }

            if(value == true)
            {
            arrayPerson *temp = new arrayPerson(id, world[targetRow][targetCol].pushToBack(id,targetRow, targetCol),true);
            world[targetRow][targetCol].population = world[targetRow][targetCol].population +1;
          }
          return value;
        }

    std::vector<int> * members(int row, int col)const{
     std::vector<int> * mem = new std::vector<int>();

      Doubly* temp = world[row][col].pHead;
      int data;
      while(temp!=nullptr)
        {
          data = temp->array->ID;
          mem->push_back(data);
          temp=temp->next;
        }

      return mem;
    }

    int population()const{

        return popul;
    }

    int population(int row, int col)const{

      return  world[row][col].population;
    }

    int num_rows()const {
      return nrow;
    }
    int num_cols()const {
      return ncol;
    }


  private:
    struct Person
    {
      int row,col;
      int ID;
    };
    struct Doubly
    {
        Person *array;
        Doubly *next;
        Doubly *prev;

    };
    class District
    {
    public:
      Doubly *pHead = nullptr;
      Doubly *pEnd = nullptr;
      int population =0;

      Doubly* pushToBack(int Id, int row, int col){

        Doubly *temp = new Doubly();

        if(pHead == nullptr)
          {
            Person *newPerson = new Person();
            newPerson->row=row;
            newPerson->col=col;
            newPerson->ID = Id;

            temp->array = newPerson;
            temp->next = nullptr;
            temp->prev = temp;
            pEnd = temp;
            pEnd->next= nullptr;
            pHead = temp;
          }else
            {
              Person *newPerson = new Person();
              newPerson->row=row;
              newPerson->col=col;
              newPerson->ID = Id;

              pEnd->next= temp;
              temp->array = newPerson;
              temp->next = nullptr;
              temp->prev = pEnd;
              pEnd = temp;
            }
          return temp;

      }


    };

    class  arrayPerson
    {
    public:
      int ID;
      Doubly* node;
      bool alive;

      arrayPerson(int iden, Doubly *ptr, bool al)
        {
          ID = iden;
          node = ptr;
          alive = al;
          return;
        }
    };
    bool validPoints(int numrow, int numcol)const{
      if (numrow >nrow || numcol > ncol){
        return false;
      }
      else if (numrow< 0 || numcol <0){
        return false;
      }
      return true;
    }

    int nrow, ncol;
    int popul;
    District **world;

    vector<int> deadpeople;
    vector<arrayPerson> peopleArray;
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.
};
