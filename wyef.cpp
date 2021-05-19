#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
using namespace std;
#define lazy const double
double startMoney = 100000;
#define space cout<<endl
#define oppSpace myF<<"\n"

const bool AUTOCLEAR = true;
const string FILENAME = "log.txt";

void adjustRound();
double fetchTotoalExpense();
void getLoan();
void printRound();
int maxItems();
int componentNum();
void hire();
void buildProduct();
double calculatePQI();
void updateStorageFee();
void updateWorkerfee();
double totalEmployeeCost();
double totalWorkerCost();
double totalEngineerCost();
void saveStatsToFile();

// ------based on city-------
struct city {
	string name = "Wuhan";

	double MaxLoan = 4200000;
	double interestRate = 3.3;
	double population = 2500000;
	double Penetration = 1.3;
	double AveragePrice = 4100;
	double averagePQI = 5;
	double averageMarketInvestment = 1000000;

	// Initial Salary
	double workerCost = 2700;
	double engineerCost = 4800;
	//Material Unit Cost
	double materialComponent = 76;
	double materialProduct = 330;
	//Storage Unit Cost
	double storageComponent = 10;
	double storageProduct = 33;

	double marketingInvest = 0;
	double marketShare = 0;
	double productPrice = 0;
	int agentNum = 0;
} startCity;

vector<city> cityList;
// ------------------------- STATS ------------------------------
double totalCost = 0;
double money = 20000000; // start with 20,000,000
double initialMoney = 20000000;
double netIncome = 0;
double income = 0;
int hoursUsed = 0;
int workersNumber = 0;
int engineerNumber = 0;
int roundNum = 0;
bool gotLoan = false;
bool build = false;
int oldProd = 0;
int productsSold = 0;
//expense
double loanMonOwed = 0;
double storageCost = 0;
double extraFees = 0;
double productionCost = 0;
double reportFee = 0;
double transportationFee = 0;
double transportEachC = 100;
double previousExpense = 0;
double totalTrainingFee = 0;
double totalLayoffFee = 0;
double investmentFee = 0;
double taxedMoney = 0;

const double incomeTax = 0.25;
//stuff
int productNumber = 0;
int componentNumber = 0;
int componentMaterialNumber = 0;
int productMaterialNumber = 0;

//invest
double productInvest = 0;
double marketingInvest = 0;

//calculated 
double PQI = 0;
double CPI = 0;
double rToH = 504;
double quaterInterestRate;
//1 round == 1 quater. 1 quater = 3 months. 1 month = 21 working days. 1 day = 8 working hours. -> 1 round = 504 hour


// PRODUCT & STORAGE
int amountSold = 0;
double productPrice = 0;
double productStorageNeeded = 0;
double componentStorageNeeded = 0;
double productStorage = 0;
double componentStorage = 0;

const double maxProdPrice = 0;
const double minProdPrice = 1;

// -----------------------------------------------------------

// PRICES
double agentCost = 300000;
double removeAgentCost = 100000;
double marketReportCost = 200000;
double workerTrainingFee = 1500;
double engineerTrainingFee = 3000;

double compMaterialCost = 76;
double prodMaterialCost = 330;
double componenetStoragePrice = 100;
double productStoragePrice = 100;
double componenetCapacityIncrement = 10;
double productCapacityIncrement = 33;

// SET 
struct component {
	const int compMaterialRequired = 1;
	const int hoursRequired = 2;
	const int workersRequried = 4;
}comp;

struct product {
	const int prodMaterialRequired = 1;
	const int hoursRequired = 7;
	const int compRequired = 8;
	const int engineersRequired = 5;
}prod;

// ******************************************************************
class employeeList {
public:
	int workerCount = 0;
	int engineerCount = 0;
	int agentCount = 0;

	int workerFired = 0;
	int EngineerFired = 0;

	int totalEmployees() {
		return workerCount + engineerCount + agentCount;
	}

	/*double workerCost = 0;
	double engineerCost = 0;
	double agentCos = 0;*/

	double totalCost = 0;

	struct employee {
		int roundHired = 0;
		int roundFired = -1;
		string type;
		double salary = 0;
		int number = 0;
		string name;
		city myC = startCity;
	};

	vector<employee> workerList;
	vector<employee> engineerList;
	vector<employee> agentList;

	void addWorker(double salary, string name) {
		workerCount++;
		//workerCost += salary;
		totalCost += salary;
		extraFees += workerTrainingFee;
		totalTrainingFee += workerTrainingFee;

		employee person;
		person.salary = salary;
		person.name = name;
		person.type = "worker";
		person.number = workerCount;
		person.roundHired = roundNum;
		workerList.push_back(person);
	};

	void addEngineer(double salary, string name) {
		engineerCount++;
		//engineerCost += salary;
		totalCost += salary;
		extraFees += engineerTrainingFee;
		totalTrainingFee += engineerTrainingFee;

		employee person;
		person.salary = salary;
		person.name = name;
		person.type = "engineer";
		person.number = engineerCount;
		person.roundHired = roundNum;
		engineerList.push_back(person);
	};

	void addAgent(double salary, string name, int a) {
		cityList[a].agentNum++;
		agentCount++;
		//agentCos += agentCost;
		totalCost += agentCost;

		employee person;
		person.salary = salary;
		person.name = name;
		person.type = "agent";
		person.number = agentCount;
		person.myC = cityList[a];
		agentList.push_back(person);
	};

	void removeEmployee() {
		if (build)
			cout << "Already Built!" << endl;
		else {
			cout << "what type? (worker-'1', engineer-'2', agent-'3')" << endl;
			int type;
			cin >> type;
			int a = 0;
			int max = 0;

			if (type == 1) {
				cout << "how many? (you have " << workerCount - workerFired << ")" << endl;
				max = workerCount - workerFired;
			}
				

			if (type == 2) {
				cout << "how many? (you have " << engineerCount - EngineerFired << ")" << endl;
				max = engineerCount - EngineerFired;
			}
				

			if (type == 3) {
				double s = 0;
				cout << "which city?" << endl;
				for (int i = 1; i <= cityList.size(); i++) {
					cout << i << ". " << cityList[i - 1].name << " (agents: " << cityList[i - 1].agentNum << ")" << endl;
				}
				cin >> a;

				cout << "how many? (you have " << cityList[a - 1].agentNum << ")" << endl;
				for (int i = 0; i < a; ) {
					if (agentList[i].myC.name == cityList[a].name) {
						s = 0;
						cityList[a].agentNum -= 1;
						agentList.erase(agentList.begin() + i);
						agentCount--;
						agentCost -= s;
						extraFees += removeAgentCost;
					}
					//s = theEmployeeList.agentList[0].salary;
				}
			}
			else {
				int number;
				cin >> number;

				if (max < number) {
					cout << "invalid number" << endl;
					number = 0;
				}

				double s = 0;

				for (int i = 0; i < number; i++) {
					if (type == 1) {
						for (int j = 0; j < workerCount; j++) {
							if (workerList[j].roundFired == -1) {
								workerList[j].roundFired = roundNum;
								s = workerList[j].salary;
								extraFees += s;
								totalLayoffFee += s;
								workerFired += 1;
								break;
							}
						}
						//workerList.erase(workerList.begin());
						//workerCount--;
						//workerCost -= s;
					}

					if (type == 2) {
						for (int j = 0; j < engineerCount; j++){
							if (engineerList[j].roundFired == -1) {
								s = engineerList[j].salary;
								engineerList[j].roundFired = roundNum;
								extraFees += s;
								totalLayoffFee += s;
								EngineerFired += 1;
								break;
							}
						}
				
						//engineerList.erase(engineerList.begin());
						//engineerCount--;
						//engineerCost -= s;

					}

					//previousExpense += ((roundNum - 1) * s * 3);
					totalCost -= s;
				}
				cout << "removed " << number << " employees" << endl;
			}
			space;
		}
	};

	void printEmployeeStats(employee person) {
		space;
		cout << "> " << person.name << " #" << person.number << endl;
		cout << "salary: " << person.salary << endl;
		if (person.type == "agent") {
			cout << "- city: " << person.myC.name << endl;
			cout << "total cost:" << agentCost << endl;
		}
		else {
			double Tcost = 0;
			cout << "round hired: " << person.roundHired << endl;
			if (person.roundFired != -1) {
				cout << "round fired: " << person.roundFired << endl;
				Tcost = (person.roundFired - person.roundHired) * person.salary * 3;
				cout << "total cost: " << person.salary << " *3 *" << (person.roundFired - person.roundHired) << " = "<<Tcost<<endl;
			}
			else {
				Tcost = (roundNum + 1 - person.roundHired) * person.salary * 3;
				cout << "total cost: " << person.salary << " *3 *" << (roundNum +1 - person.roundHired) << " = " << Tcost << endl;
			}
			
		}
	}
private:

} theEmployeeList;

double totalWorkerCost() {
	double cost = 0;
	double Tcost = 0;
	for (int i = 0; i < theEmployeeList.workerCount; i++) {
		if (theEmployeeList.workerList[i].roundFired != -1) {
			Tcost = (theEmployeeList.workerList[i].roundFired - theEmployeeList.workerList[i].roundHired) * theEmployeeList.workerList[i].salary * 3;
		}
		else {
			Tcost = (roundNum + 1 - theEmployeeList.workerList[i].roundHired) * theEmployeeList.workerList[i].salary * 3;
		}
		cost += Tcost;
	}
	return cost;
}

double totalEngineerCost() {
	double cost = 0;
	double Tcost = 0;
	for (int i = 0; i < theEmployeeList.engineerCount; i++) {
		if (theEmployeeList.engineerList[i].roundFired != -1) {
			Tcost = (theEmployeeList.engineerList[i].roundFired - theEmployeeList.engineerList[i].roundHired) * theEmployeeList.engineerList[i].salary * 3;
		}
		else {
			Tcost = (roundNum + 1 - theEmployeeList.engineerList[i].roundHired) * theEmployeeList.engineerList[i].salary * 3;
		}
		cost += Tcost;
	}

	return cost;
}



double totalEmployeeCost() {
	double cost = 0;
	double Tcost = 0;
	for (int i = 0; i < theEmployeeList.workerCount; i++) {
		if (theEmployeeList.workerList[i].roundFired != -1) {
			Tcost = (theEmployeeList.workerList[i].roundFired - theEmployeeList.workerList[i].roundHired) * theEmployeeList.workerList[i].salary * 3;
		}
		else {
			Tcost = (roundNum + 1 - theEmployeeList.workerList[i].roundHired) * theEmployeeList.workerList[i].salary * 3;
		}
		cost += Tcost;
	}

	for (int i = 0; i < theEmployeeList.engineerCount; i++) {
		if (theEmployeeList.engineerList[i].roundFired != -1) {
			Tcost = (theEmployeeList.engineerList[i].roundFired - theEmployeeList.engineerList[i].roundHired) * theEmployeeList.engineerList[i].salary * 3;
		}
		else {
			Tcost = (roundNum + 1 - theEmployeeList.engineerList[i].roundHired) * theEmployeeList.engineerList[i].salary * 3;
		}
		cost += Tcost;
	}

	for (int i = 0; i < theEmployeeList.agentCount; i++)
		cost += agentCost;

	return cost;
}

double calculatePQI() {
	// PQI = quality investment / (old product x 1.2 + new products)
	if ((oldProd * 1.2 + (productNumber - oldProd)) == 0)
		return 0;
	else
		return productInvest / (oldProd * 1.2 + (productNumber - oldProd));
}

double fetchTotoalExpense() {
	return loanMonOwed + totalEmployeeCost() + extraFees + productionCost + storageCost + transportationFee + investmentFee;
}

void updateMoney() {
	
	money = initialMoney + income + loanMonOwed -fetchTotoalExpense();
	money += loanMonOwed;
}

void buy() {

}

void getLoan() {
	
	if (!gotLoan) {
		int loanAmt;
		cout << "CITY MAX = $" << startCity.MaxLoan << endl;
		cout << "how much $?: $";
		cin >> loanAmt;

		if (loanAmt > 0) {
			if (loanAmt > startCity.MaxLoan)
				cout << "TOO LARGE - EXCEEDS CITY MAX" << endl;
			else {
				money += loanAmt;
				loanMonOwed += loanAmt;
			}
			cout << "success" << endl;
			gotLoan = true;
		}
		else {
			cout << "don't do this to me... pain to code 5 extra lines cuz you didn't get an actual loan - ALAN" << endl;
		}
	}
	else {
		cout << "ALREADY GOT LOAN" << endl;
	}
}

void printRound() {
	updateStorageFee();
	space;
	cout << "############################ ROUND #"<<roundNum<<" ##################################" << endl;
	updateMoney();
	cout << "Money: $" << money<<endl;
	
	space;
	cout << "          ### Products ###" << endl;
	cout << "number of products: " << productNumber << endl;
	cout << "average product price: " << productPrice << endl; // average*
	cout << "components left: " << componentNumber << endl;
	cout << "quality investment: " << productInvest << endl;
	cout << "Marketing investment: " << marketingInvest << endl;
	cout << "PQI: " << calculatePQI() << endl;
	cout << "Product Storage Needed: " << productStorageNeeded << endl;
	cout << "Total Product Storage: " << productStorage << endl;
	cout << "Product Storage used: " << productNumber << endl;
	cout << "Componet Storage Needed: " << componentStorageNeeded << endl;
	cout << "Total Componet Storage: " << componentStorage << endl;
	cout << "Component Storage used: " << componentNumber << endl;

	space;
	cout << "          ### Employees ###" << endl;
	space;
	cout <<theEmployeeList.workerCount - theEmployeeList.workerFired<<" workers:"<<endl;
	for (int i = 0; i < theEmployeeList.workerCount; i++)
		theEmployeeList.printEmployeeStats(theEmployeeList.workerList[i]);
	space;
	cout << theEmployeeList.engineerCount - theEmployeeList.EngineerFired<< " engineers:" << endl;
	for (int i = 0; i < theEmployeeList.engineerCount; i++)
		theEmployeeList.printEmployeeStats(theEmployeeList.engineerList[i]);
	space;
	cout << theEmployeeList.agentCount << " agents:" << endl;
	for (int i = 0; i < theEmployeeList.agentCount; i++)
		theEmployeeList.printEmployeeStats(theEmployeeList.agentList[i]);

	space;
	cout << "          ###  Expense ###" << endl;
	space;
	cout << "> Loan Money Owed: $" << loanMonOwed<< endl;
	cout << "> Report Costs: $" << reportFee << endl;
	cout << "> Transportation: $" << transportationFee << endl;
	cout << "> Total Storage cost: $" << storageCost << endl;
	cout << "> Total Investment cost: $" << investmentFee << endl;
	space;
	cout << "Worker Cost: $" << totalWorkerCost() << endl;
	cout << "Engineer Cost: $" << totalEngineerCost() << endl;
	cout << "Agent Cost: $" << theEmployeeList.agentCount * agentCost << endl;
	cout << "> Total Employee Cost (start of next round): $" << totalEmployeeCost()<< endl;
	space;
	cout << "Total Training Fee: $" << totalTrainingFee << endl;
	cout << "Total Layoff Fee: $" << totalLayoffFee << endl;
	cout << "> Extra Fees: $" << extraFees << endl;
	space;
	cout << "> Production Cost: $" << productionCost << endl;
	cout << "*** Total Expense **** : $" << fetchTotoalExpense() << endl;

	space;
	cout << "          ###   Income  ###" << endl;
	cout << "*** Total Income ****: $" << income << endl;
	
	netIncome = income - fetchTotoalExpense();

	space;
	cout << "          ****** Net Income (worker salary this Round) ****" << endl << "              $" << netIncome + (totalEmployeeCost()> previousExpense ? (totalEmployeeCost() - previousExpense):0)<< endl;
	cout << "          ****** Net Income (worker salary next Round) ****" << endl << "              $" << netIncome << endl;
	space;
	cout << "######################################################################" <<endl;
	space;
}


void printCity(city a) {
	cout << "############ " + a.name + " ###############" << endl;
	cout << "- Max Loan: $" << a.MaxLoan << endl;
	cout << "- interestRate: $" << a.interestRate << endl;
	cout << "- population: $" << a.population << endl;
	cout << "- Penetration: $" << a.Penetration << endl;
	cout << "- Average Price: $" << a.AveragePrice << endl;
	cout << "- worker Cost: $" << a.workerCost << endl;
	cout << "- engineer Cost: $" << a.engineerCost << endl;
	cout << "- material Component: $" << a.materialComponent << endl;
	cout << "- material Product: $" << a.materialProduct << endl;
	cout << "- agents: " << a.agentNum << endl;
	cout << "##########################################"<<endl;
	space;
}

void addCity(string name, double maxL, double intR, double pop, double pen, double avgPrice, double workerCost, double engineerCost, double materialComp, double materialProd, double storageComp, double storageProd) {
	city myC;
	myC.name = name;

	myC.MaxLoan = maxL;
	myC.interestRate = intR;
	myC.population = pop;
	myC.Penetration = pen;
	myC.AveragePrice = avgPrice;
	// Initial Salary
	myC.workerCost = workerCost;
	myC.engineerCost = engineerCost;
	//Material Unit Cost
	myC.materialComponent = materialComp;
	myC.materialProduct = materialProd;
	//Storage Unit Cost
	myC.storageComponent = storageComp;
	myC.storageProduct = storageProd;

	cityList.push_back(myC);
}


void hire() {
	if (build)
		cout << "Already Built! " << endl;
	else {
		cout << "\twhat type? (worker-'1', engineer-'2', agent-'3')" << endl;
		int type;
		int n;
		string theName;
		double salary = 0;
		double idealSalary;
		cin >> type;

		switch (type) {
		case 1: idealSalary = startCity.workerCost; break;
		case 2: idealSalary = startCity.engineerCost; break;
		case 3: idealSalary = agentCost; break;
		}
		if (type != 3) {
			cout << "\twhat's his/her salary?" << endl;
			cin >> salary;
			if (salary < idealSalary)
				cout << "(Your Employee hates you >:( because you pay him lower than the market price)" << endl;
		}

		cout << "\twhat's his/her name?" << endl;
		cin >> theName;

		int i = 0;
		double fee = type == 1 ? workerTrainingFee : (type == 2 ? engineerTrainingFee : 0);

		if (type == 3) {
			cout << "cost: " << agentCost << endl;
			cout << "how many?" << endl;
			for (int j = 0; j < cityList.size() && agentCost < money; j++) {
				updateMoney();
				cout << cityList[j].name << " :";
				int a;
				cin >> a;

				for (i = 0; i < a; i++) {
					theEmployeeList.addAgent(0, "Bad Agent", j);
				}
			}

		}
		else {
			cout << "\tHow many do you want to hire?" << endl;
			cin >> n;

			for (i = 0; i < n && (salary * 3) + fee <= money; i++) {
				updateMoney();
				if ((salary * 3) + fee <= money) {
					if (type == 1)
						theEmployeeList.addWorker(salary, "Useless Worker");

					if (type == 2)
						theEmployeeList.addEngineer(salary, "Lazy Engineer");

				}
				else {
					cout << "NOT ENOUGH MONEY (cuz you poor)" << endl;
				}
			}
		}
		space;
		cout << "hired: " << i << " employees";
	}
}


void updateStorageFee() {
	if (productNumber > productStorage) { //storage is needed
		productStorageNeeded = productNumber - productStorage;
		productStorage += productStorageNeeded;
		storageCost += productStorageNeeded * productCapacityIncrement;
		productStorageNeeded = 0;
	}

	if (componentNumber > componentStorage) { //storage is needed
		componentStorageNeeded = componentNumber - componentStorage;
		componentStorage += componentNumber;
		storageCost += componentStorageNeeded * componenetCapacityIncrement;
		componentStorageNeeded = 0;
	}
}

double calculateMarketShare(city myC) {
	myC.marketShare = (myC.AveragePrice / (myC.productPrice * 1.2)) * 0.2 + (calculatePQI() / (myC.averagePQI * 1.2)) * 0.2 + (marketingInvest*myC.agentNum/ (myC.averageMarketInvestment * 1.2)) * 0.2;
	
	//debug
	//cout << myC.AveragePrice << " " << productPrice << endl;
	//cout << (myC.AveragePrice / (productPrice * 1.2)) * 0.2 <<endl;
	//cout << (PQI / (myC.averagePQI * 1.2)) * 0.2 << endl;
	//cout << (marketingInvest / (myC.averageMarketInvestment * 1.2)) * 0.2 << endl;
	//
	//cout << myC.marketShare << endl;

	myC.marketShare = myC.marketShare/ 2;
	if (myC.marketShare < 0)
		myC.marketShare = 0;

	return myC.marketShare;
	// your PQI / average PQI + pricing PQI/ avg
	// marketshare = PQI * 20% + pricing * 20% + marketing * 20
	// abs |avg price - price| > 5% * avg price ?  avg price - price /  5% * avg price : 0
	// 
}

int sellableProducts(city myC) {                                                                                                                    
	//sellable p = product < marketshare% * city.market pop * Penetration

	return productNumber < (calculateMarketShare(myC) * myC.population* myC.Penetration) ? productNumber : (calculateMarketShare(myC) * myC.population * myC.Penetration);
}

int maxItems() {
	int workerWorkH = (theEmployeeList.workerCount -theEmployeeList.workerFired) * rToH;
	int engineerWorkH = (theEmployeeList.engineerCount-theEmployeeList.EngineerFired) * rToH;
	int maxComp = workerWorkH/ (comp.hoursRequired * comp.workersRequried);
	componentNumber = maxComp<(money/startCity.materialComponent)?maxComp: (money / startCity.materialComponent);
	
	int maxProd = (engineerWorkH - comp.hoursRequired) / (prod.hoursRequired * prod.engineersRequired);
	//productNumber = maxProd < (money / startCity.materialProduct) ? maxProd : (money / startCity.materialProduct);

	int maxPrice = money / (comp.compMaterialRequired * compMaterialCost + prod.prodMaterialRequired * prodMaterialCost);
	
	return ((maxComp/prod.compRequired)<maxProd&&(maxComp / prod.compRequired)<maxPrice) ? (maxComp / prod.compRequired): (maxProd<maxPrice ? maxProd:maxPrice);

}

int componentNum() {
	int workerWorkH = (theEmployeeList.workerCount-theEmployeeList.workerFired) * rToH;
	int maxComp = workerWorkH / (comp.hoursRequired * comp.workersRequried);
	componentNumber = maxComp < (money / startCity.materialComponent) ? maxComp : (money / startCity.materialComponent);
	return componentNumber;
}



void buildProduct() {
	if (build)
		cout << "Alrady Built!" << endl;
	else {
		cout << "\tHow many products do you want to produce? (max = " << maxItems() << " products. You have " << componentNum() << " components this round)";
		int i;
		cin >> i;
		if (i <= maxItems()) {
			productNumber += i;
			productionCost += (comp.compMaterialRequired * compMaterialCost * prod.compRequired * i + prod.prodMaterialRequired * prodMaterialCost * i);
			cout << "\tproduction cost: " << productionCost << endl;
			int compUsed = prod.compRequired * i;
			componentNumber -= compUsed;
			cout << "\tcomponents left: " << componentNumber << endl;

			cout << "success" << endl;
			cout << "\tHow much do you want to sell them for?" << endl;
			for (int i = 0; i < cityList.size(); i++) {
				cout << cityList[i].name << "'s price: ";
				cin >> cityList[i].productPrice;
				productPrice += cityList[i].productPrice;
			}
			productPrice = productPrice / cityList.size();
			build = true;
		}
		else {
			cout << "too much" << endl;
		}
		space;
	}
}

void adjustRound() {
	saveStatsToFile();
	previousExpense = totalEmployeeCost();
	updateWorkerfee();
	space;
	cout << "---------- calculating.... -----------" << endl;
	cout << "\tQuater Interest Rate: " << quaterInterestRate << endl;

	for (int i = 0; i < cityList.size(); i++) {
		productsSold = 0;
		cout << "_____________________________" << endl;
		cout <<"\t"<< cityList[i].name<<"'s Estimated Market Share: " << calculateMarketShare(cityList[i])<< endl;
		//income += (sellableProducts(cityList[i]) * cityList[i].productPrice);
		cout << "\tYour Estimated Market Size: " << (calculateMarketShare(cityList[i]) * cityList[i].population * cityList[i].Penetration) << " people"<< endl;
		cout << "\tEnter Products Sold: "; 
		cin>>productsSold;
		//cout << "\tSold products: " << (sellableProducts(cityList[i])) << endl;
		income += productsSold * cityList[i].productPrice;
		transportationFee += (i == 0 ? 0 : (transportEachC * productsSold));
		cout << "\tTransportation Fee: " << (i == 0 ? 0 : (transportEachC * productsSold)) << endl;
		cout << "\tIncome: " << (productsSold * cityList[i].productPrice) << endl;
		productNumber -= productsSold;
		cout << "_____________________________" << endl;
	}
	//cout << "Market Share: " << marketShare << endl;
	productInvest = 0;
	//extraFees = 0;
	//reportFee = 0;
	loanMonOwed = loanMonOwed + loanMonOwed * quaterInterestRate;
	if (loanMonOwed <= income) {
		income -= loanMonOwed;
		loanMonOwed = 0;
	}
	cout << "\tLoan Money Owed: " << loanMonOwed << " + " << loanMonOwed * quaterInterestRate << " = ";
	cout << loanMonOwed << endl;
	
	cout << "---------------------------------------" << endl;
	space;
	oldProd = productNumber;
	roundNum++;
	updateWorkerfee();
	saveStatsToFile();
}

void updateWorkerfee() {
	theEmployeeList.totalCost *= roundNum;
}

void invest() {
	cout << "\twhat do you want to invest in? (1-quality, 2-marketing)" << endl;
	int option;
	cin >> option;
	if (option == 1) {
		cout << "\thow much do you want to invest? " << endl;
		cin >> productInvest;

		if (productInvest <= money) {
			PQI = productInvest;
			investmentFee += productInvest;
		}
		else {
			cout << "too much money" << endl;
		}
	}
	
	if (option ==2){
		cout << "\twhich city? 1-" << cityList.size() << endl;
		for (int i = 0; i < cityList.size(); i++)
			cout << cityList[i].name << "-" << i + 1 << endl;
		int i = 0;
		cin >> i;

		cout << "\thow much do you want to invest? " << endl;
		cin >> marketingInvest;

		if (marketingInvest <= money) {
			cityList[i - 1].marketingInvest = marketingInvest;
			investmentFee += marketingInvest;
		}
		else {
			cout << "too much money" << endl;
		}
	}

}

void addC(){
	string name;
	double pop, pen, avgPrice;
	cout << "\tEnter Name: ";
	cin >> name;
	cout << "\tEnter Population: ";
	cin >> pop;
	cout << "\tEnter Penetration: ";
	cin >> pen;
	cout << "\tEnter Average Price: ";
	cin >> avgPrice;
	
	addCity(name,0,0,pop,pen,avgPrice,0,0,0,0,0,0);
}

void buyReport() {
	cout << "\thow many reports?" << endl;
	int i;
	cin >> i;
	reportFee += (i * marketReportCost);
}

void saveStatsToFile() {
	ofstream myF;
	myF.open(FILENAME, ofstream::app);
	myF << fixed;
	updateStorageFee();
	oppSpace;

	myF << "############################ ROUND #" << roundNum << " ##################################" << endl;
	updateMoney();
	myF << "Money: $" << money << endl;

	oppSpace;
	myF << "          ### Products ###" << endl;
	myF << "number of products: " << productNumber << endl;
	myF << "average product price: " << productPrice << endl; // average*
	myF << "components left: " << componentNumber << endl;
	myF << "quality investment: " << productInvest << endl;
	myF << "Marketing investment: " << marketingInvest << endl;
	myF << "PQI: " << calculatePQI() << endl;
	myF << "Product Storage Needed: " << productStorageNeeded << endl;
	myF << "Total Product Storage: " << productStorage << endl;
	myF << "Product Storage used: " << productNumber << endl;
	myF << "Componet Storage Needed: " << componentStorageNeeded << endl;
	myF << "Total Componet Storage: " << componentStorage << endl;
	myF << "Component Storage used: " << componentNumber << endl;

	oppSpace;
	myF << "          ### Employees ###" << endl;
	oppSpace;
	myF << theEmployeeList.workerCount - theEmployeeList.workerFired << " workers:" << endl;
	oppSpace;
	myF << theEmployeeList.engineerCount - theEmployeeList.EngineerFired << " engineers:" << endl;
	oppSpace;
	myF << theEmployeeList.agentCount << " agents:" << endl;

	oppSpace;
	myF << "          ###  Expense ###" << endl;
	oppSpace;
	myF << "> Loan Money Owed: $" << loanMonOwed << endl;
	myF << "> Report Costs: $" << reportFee << endl;
	myF << "> Transportation: $" << transportationFee << endl;
	myF << "> Total Storage cost: $" << storageCost << endl;
	myF << "> Total Investment cost: $" << investmentFee << endl;
	oppSpace;
	myF << "Worker Cost: $" << totalWorkerCost() << endl;
	myF << "Engineer Cost: $" << totalEngineerCost() << endl;
	myF << "Agent Cost: $" << theEmployeeList.agentCount * agentCost << endl;
	myF << "> Total Employee Cost (start of next round): $" << totalEmployeeCost() << endl;
	oppSpace;
	myF << "Total Training Fee: $" << totalTrainingFee << endl;
	myF << "Total Layoff Fee: $" << totalLayoffFee << endl;
	myF << "> Extra Fees: $" << extraFees << endl;
	oppSpace;
	myF << "> Production Cost: $" << productionCost << endl;
	myF << "*** Total Expense **** : $" << fetchTotoalExpense() << endl;

	oppSpace;
	myF << "          ###   Income  ###" << endl;
	myF << "*** Total Income ****: $" << income << endl;

	netIncome = income - fetchTotoalExpense();

	space;
	myF << "          ****** Net Income (worker salary this Round) ****" << endl << "              $" << netIncome + (totalEmployeeCost() > previousExpense ? (totalEmployeeCost() - previousExpense) : 0) << endl;
	myF << "          ****** Net Income (worker salary next Round) ****" << endl << "              $" << netIncome << endl;
	space;
	myF << "######################################################################" << endl;

	myF.close();
}

int main() {
	cout << "banana" << endl;

	if (AUTOCLEAR) {
		ofstream myF;
		myF.open(FILENAME, ofstream::trunc);
		myF.close();
		cout << "File Cleared - auto clear on" << endl;
	}
	
	cityList.push_back(startCity);
	quaterInterestRate = startCity.interestRate / 4;
	cout << fixed;
	
	char in = ' ';
	roundNum++;
	while (in != 'q') {
		for (int i=0; i<cityList.size(); i++)
			printCity(cityList[i]);
		in = ' ';
		gotLoan = false;
		build = false;
		while (in != 'c' && in != 'q') {
			cout << "-----------------------------------------------------------------------------" << endl;
			cout << "\t what do you wanna do? \n ('c' to continue to next round, 'r' to buy a report, 'a' to add city, 'i' to invest, 'b' to build products, 's' to check stats, 'l' to get a loan, 'h' to hire, 'f' to layoff, 'q' to quit)" << endl;
			in = _getch();
			in = tolower(in);
			space;
			updateMoney();
			switch (in) {
			case 'a': addC(); break;
			case 'c': space;  printRound(); adjustRound(); printRound(); break;
			case 's': printRound(); break;
			case 'l': getLoan(); break;
			case 'h': hire();break;
			case 'f': theEmployeeList.removeEmployee();break;
			case 'q': break;
			case 'r': buyReport(); break;
//			case 'p': sellProduct(); break;
			case 'b': buildProduct(); break;
			case 'i': invest(); break;
			default:  break;
			}

			space;
			
		}
		space;
	}


	return 0;
}
