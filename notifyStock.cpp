#include <iostream>
using namespace std;
#include<list>

class NotificationAlertObserver{
    public:
      virtual void update(){}
};

class StockObservable{
  public:
    virtual void add(NotificationAlertObserver *){}
    virtual void remove_observer(NotificationAlertObserver *){}
    virtual void notifySubscribers(){}
    virtual void setStockCount(int newStockAdded){}
    virtual int getStockCount(){return 0;}
};

class iphoneObservable : public StockObservable{
  public:
    list<NotificationAlertObserver*> observerList;
    int stockCount=0;
    
    void add(NotificationAlertObserver *observer){
        observerList.push_back(observer);
    }
    
    void remove_observer(NotificationAlertObserver *observer){
        observerList.remove(observer);
    }
    
    void notifySubscribers(){
        for(auto observer : observerList){
            observer->update();
        }
    }
    
    void setStockCount(int newStockAdded){
        if(stockCount==0){
            notifySubscribers();
        }
        
        stockCount += newStockAdded;
    }
    
    int getStockCount(){
        return stockCount;
    }
    
};

class EmailAlertObserver : public NotificationAlertObserver{
  public:
    string emailId;
    StockObservable *observable;
    
    EmailAlertObserver(string email, StockObservable *observable){
        this->emailId = email;
        this->observable = observable;
    }
    
    void update(){
        cout<<emailId<<" , product is in stock hurry up!"<<endl;
    }
};

class MobileAlertObserver : public NotificationAlertObserver{
  public:
    string mobileNumber;
    StockObservable *observable;
    
    MobileAlertObserver(string mobileNumber, StockObservable *observable) {
        this->mobileNumber = mobileNumber;
        this->observable = observable;
    }
    
    void update(){
        cout<<mobileNumber<<" , product is in stock hurry up!"<<endl;
    }
};

int main()
{
    
    StockObservable *iphoneObser = new iphoneObservable();
    
    NotificationAlertObserver *obeserver1 = new EmailAlertObserver("atul@gmail.com",iphoneObser);
    NotificationAlertObserver *obeserver2 = new MobileAlertObserver("6876827989",iphoneObser);
    
    iphoneObser->add(obeserver1);
    iphoneObser->add(obeserver2);
    iphoneObser->setStockCount(10);

    return 0;
}
