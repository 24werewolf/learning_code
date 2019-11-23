
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Movie{

public:
  enum TYPE{

  REGULAR,
  NEW_RELEASE,
  CHILDRENS

  };

private:
  string _movieName;
  int _priceCode;

public:

  //Movie() {};

  Movie(string movieName, int priceCode): _movieName(movieName), _priceCode(priceCode){} ;   // 带参数的构造函数的初始化列表

  //~Movie() {};

  int getPriceCode();

  void setPriceCode(int arg);

  string getMovieName();

  double getCharge(int daysRented);

  int getFrequentRenterPoints(int daysRented);

};

int  Movie::getPriceCode(){

  return _priceCode;
}

void Movie::setPriceCode(int arg){
    _priceCode = arg;

}

string Movie::getMovieName(){

  return _movieName;

}

double Movie::getCharge(int daysRented){

  double result = 0;


    switch(getPriceCode()){
    case Movie::REGULAR:
      result += 2;
    if(daysRented>2)
      result += (daysRented-2)*1.5;
    break;

    case Movie::NEW_RELEASE:
        result += daysRented*3;
    break;

    case Movie::CHILDRENS:
      result += 1.5;
      if(daysRented>3)
        result += (daysRented-3)*1.5;
    break;
  }

    return result;
    
}


int Movie::getFrequentRenterPoints(int daysRented){
    if ((getPriceCode() == Movie::NEW_RELEASE) &&
    daysRented > 1) return 2;
  else
    return 1;
}




class Rental{

  private:
    Movie _movie;
    int _daysRented;

  public:
    Rental(Movie movie, int daysRented):_movie(movie),_daysRented(daysRented){};


    ~Rental() {};

    int getDaysRented();

    Movie getMovie();

    double getCharge();

    int getFrequentRenterPoints();


};



int Rental::getDaysRented(){

  return _daysRented;

}

Movie Rental::getMovie(){
  return _movie;

}



double Rental::getCharge(){

  return _movie.getCharge(_daysRented);
    
}



int Rental::getFrequentRenterPoints(){
  return _movie.getFrequentRenterPoints(_daysRented);

}





typedef vector<Rental> Vector;  // 为复杂声明一个简单的别名

typedef vector<Rental>::iterator Reniter;  //为复杂声明一个简单的别名



/*

迭代器(interator) 是一种检查容器内元素并遍历元素的数据类型

每种容器都定义了自己的迭代器类型。

vector<int>::iterator iter; 
这条语句定义了一个名为iter的变量，它的数据类型是由vector<int>定义的iterator类型
*/


class Customer{
private:
  string _name;
  Vector _rentals;

public:

  Customer(string name):_name(name) {};

  void addRental(Rental arg);

  string getName();

  string statement();

  double amountFor(Rental each);


};

/*
Customer::Customer(string name){

  _name = name;
}
*/
void Customer::addRental(Rental arg){
  _rentals.push_back(arg);

}


string Customer::getName(){
  return _name;
}




double Customer::amountFor(Rental aRental){

  double result = 0;


    switch(aRental.getMovie().getPriceCode()){
    case Movie::REGULAR:
      result += 2;
    if(aRental.getDaysRented()>2)
      result += (aRental.getDaysRented()-2)*1.5;
    break;

    case Movie::NEW_RELEASE:
        result += aRental.getDaysRented()*3;
    break;

    case Movie::CHILDRENS:
      result += 1.5;
      if(aRental.getDaysRented()>3)
        result += (aRental.getDaysRented()-3)*1.5;
    break;
  }

    return result;

}



string Customer::statement(){

  double totalAmount = 0;
  int frequentRenterPoints = 0;

  Reniter iter;

  char amount[32];
  string result = string("Rental Record for ") + getName() + string("\n");

  for (iter = _rentals.begin(); iter != _rentals.end(); ++ iter){

  
    Rental each = *iter;   // （*） 迭代器类型可以使用解引用操作符（dereference  operator ） 来访问迭代器所指向的元素

    // add frequent renter points?
   frequentRenterPoints += each.getFrequentRenterPoints();
   // show figures for this rental?
   snprintf(amount, 32,"%f\n",each.getCharge());
   result += string("\t") + each.getMovie().getMovieName() + string("\t") +
    string(amount);
   totalAmount += each.getCharge();

  }


  snprintf(amount, 32, "%f\n",totalAmount);
  result += string("Amount owed is ") + string(amount);
  snprintf(amount, 32,"%d",frequentRenterPoints);
  result += string("You earned ") + string(amount) +
  string(" frequent renter points");
  return result;
}



int main(int argc, char* argv[])
{
 cout<<"Refactoring, a First Example, step1"<<endl;

 Movie m1 = Movie("Seven", Movie::NEW_RELEASE);
 Movie m2 = Movie("Terminator", Movie::REGULAR);
 Movie m3 = Movie("Star Trek", Movie::CHILDRENS);

 Rental r1 = Rental(m1, 4);
 Rental r2 = Rental(m1, 2);
 Rental r3 = Rental(m3, 7);
 Rental r4 = Rental(m2, 5);
 Rental r5 = Rental(m3, 3);

 Customer c1 = Customer("jjhou");
 c1.addRental(r1);
 c1.addRental(r4);

 Customer c2 = Customer("gigix");
 c2.addRental(r1);
 c2.addRental(r3);
 c2.addRental(r2);

 Customer c3 = Customer("jiangtao");
 c3.addRental(r3);
 c3.addRental(r5);

 Customer c4 = Customer("yeka");
 c4.addRental(r2);
 c4.addRental(r3);
 c4.addRental(r5);

 cout <<c1.statement() <<endl;
 cout <<c2.statement() <<endl;
 cout <<c3.statement() <<endl;
 cout <<c4.statement() <<endl;
 
 return 0;
}


