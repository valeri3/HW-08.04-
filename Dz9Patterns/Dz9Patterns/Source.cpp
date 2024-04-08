#include <iostream>
#include <vector>
#include <string>
#include <clocale>

using namespace std;

class Observer
{
public:
	virtual void Update(const string& product) = 0;
};

class Subject
{
protected:
	vector<Observer*> observers;

public:
	virtual void Attach(Observer* observer)
	{
		observers.push_back(observer);
	}

	virtual void Detach(Observer* observer)
	{
		observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
	}

	virtual void Notify(const string& product)
	{
		for (Observer* observer : observers)
		{
			observer->Update(product);
		}
	}
};

class Shop : public Subject
{
public:
	void NewProductArrived(const string& product)
	{
		cout << "������� ������� ����� �����: " << product << endl;
		Notify(product);
	}
};

class Customer : public Observer
{
private:
	string name;
	int age;
	vector<string> purchases;

public:
	Customer(const string& name, int age)
	{
		this->name = name;
		this->age = age;
	}

	void Update(const string& product) override
	{
		cout << name << " (" << age << " ���) �����(�) � ��������� ������ ������: " << product << "    ";
		BuyProduct(product);
	}

	void BuyProduct(const string& product)
	{
		cout << "� �����(�) ���." << endl;
		purchases.push_back(name + " �����(�) " + product);
	}

	void ShowPurchases()
	{
		for (const auto& purchase : purchases)
		{
			cout << purchase << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");

	Shop* shop = new Shop;
	Customer* customer1 = new Customer("���������� 1 ����", 25);
	Customer* customer2 = new Customer("���������� 2 �����", 30);
	Customer* customer3 = new Customer("���������� 3 ����", 22);
	Customer* customer4 = new Customer("���������� 4 ����", 28);
	Customer* customer5 = new Customer("���������� 5 ����", 35);

	shop->Attach(customer1);
	shop->Attach(customer2);
	shop->Attach(customer3);
	shop->Attach(customer4);
	shop->Attach(customer5);

	shop->NewProductArrived("�������");

	cout << endl;

	shop->Detach(customer1);
	shop->Detach(customer3);

	shop->NewProductArrived("��������");

	cout << endl;

	cout << "������ ���� �������:" << endl;

	customer1->ShowPurchases();
	customer2->ShowPurchases();
	customer3->ShowPurchases();
	customer4->ShowPurchases();
	customer5->ShowPurchases();

	delete customer1;
	delete customer2;
	delete customer3;
	delete customer4;
	delete customer5;

	system("pause");

}
