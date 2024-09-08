#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

struct UserData
{
    int age;
    double annualIncome;
    double currentSavings;
};

/// Function to calculate retirement savings target
double calculateRetirementTarget(int age, double annualIncome)
{
    int yearsUntilRetirement = 65 - age;
    double retirementTarget = annualIncome * 0.8 * 20;  // Assume 80% income for 20 years
    return retirementTarget / pow(1.07, yearsUntilRetirement); // Assume 7% annual investment return
}

// Function to provide investment advice
string getInvestmentAdvice(int age)
{
    if (age < 30)
    {
        return "Focus on aggressive growth. Allocate 80-90% to stocks.";
    }
    else if (age < 40)
    {
        return "Moderate growth. Allocate 70-80% to stocks, the rest to bonds.";
    }
    else if (age < 50)
    {
        return "Start being more conservative. 60-70% stocks, 30-40% bonds.";
    }
    else if (age < 60)
    {
        return "Be more cautious. 50-60% stocks, 40-50% bonds.";
    }
    else
    {
        return "Conservative. 30-40% stocks, 60-70% bonds and safe instruments.";
    }
}
// Function to calculate simple monthly budget
void calculateBudget(double monthlyIncome)
{
    cout << "Recommended Monthly Budget:\n";
    cout << "Needs (50%): $" << fixed << setprecision(2) << monthlyIncome * 0.5 << endl;
    cout << "Wants (30%): $" << monthlyIncome * 0.3 << endl;
    cout << "Savings (20%): $" << monthlyIncome * 0.2 << endl;
}

// New function for home purchase planning
double calculateMortgagePayment(double housePrice, int loanTerm, double interestRate)
{
    double monthlyInterestRate = interestRate / 12 / 100;
    int totalMonths = loanTerm * 12;
    return housePrice * monthlyInterestRate * pow(1 + monthlyInterestRate, totalMonths) / (pow(1 + monthlyInterestRate, totalMonths) - 1);
}

// New function for child education planning
double calculateEducationCost(double initialFee, int startYear, int duration, double annualInflation)
{
    double totalCost = 0;
    for (int i = 0; i < duration; i++)
    {
        totalCost += initialFee * pow(1 + annualInflation / 100, startYear + i);
    }
    return totalCost;
}

// New function for life insurance needs calculation
double calculateLifeInsuranceNeeds(double annualIncome, int age, int retirementAge)
{
    int workingYears = retirementAge - age;
    return annualIncome * workingYears * 0.6; // Assume 60% income needs to be replaced
}

// Function to save user data
void saveData(const UserData &data)
{
    ofstream file("user_data.csv", ios::app);
    if (file.is_open())
    {
        file << data.age << "," << data.annualIncome << "," << data.currentSavings << "\n";
        file.close();
    }
}

// Function to read user data
vector<UserData> readData()
{
    vector<UserData> dataList;
    ifstream file("user_data.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        UserData data;
        string temp;
        getline(ss, temp, ',');
        data.age = stoi(temp);
        getline(ss, temp, ',');
        data.annualIncome = stod(temp);
        getline(ss, temp, ',');
        data.currentSavings = stod(temp);
        dataList.push_back(data);
    }
    return dataList;
}

// Add new function to display comparison table
void displayComparisonTable(const vector<double> &data, const vector<string> &labels)
{
    cout << "\nFinancial Comparison Table:\n";
    cout << string(70, '-') << "\n";
    cout << setw(25) << left << "Category" << "|" 
         << setw(20) << right << "Value ($)" << " |" 
         << setw(20) << right << "Percentage" << "\n";
    cout << string(70, '-') << "\n";

    double total = accumulate(data.begin(), data.end(), 0.0);

    for (size_t i = 0; i < data.size(); ++i)
    {
        cout << setw(25) << left << labels[i] << "|" 
             << setw(20) << right << fixed << setprecision(2) << data[i] << " |"
             << setw(19) << right << fixed << setprecision(2) << (data[i] / total * 100) << "%\n";
    }

    cout << string(70, '-') << "\n";
    cout << setw(25) << left << "Total" << "|" 
         << setw(20) << right << fixed << setprecision(2) << total << " |"
         << setw(19) << right << "100.00%\n";
    cout << string(70, '-') << "\n";
}

void displayMenu() {
    cout << "\nFinance Planner Menu:\n";
    cout << "1. Input New Data\n";
    cout << "2. View Financial Analysis\n";
    cout << "3. View Data History\n";
    cout << "4. Simulate Scenario\n";
    cout << "5. Export Data to CSV\n";
    cout << "6. Add Financial Goal\n";
    cout << "7. View Financial Goals\n";
    cout << "8. Calculate Income Tax\n";
    cout << "9. Create Periodic Financial Report\n";
    cout << "10. Currency Conversion\n";
    cout << "11. Exit\n";
    cout << "Choose an option (1-11): ";
}

void inputNewData(UserData &userData) {
    while (true)
    {
        cout << "Enter your age: ";
        if (cin >> userData.age && userData.age > 0 && userData.age < 120)
            break;
        cout << "Invalid input. Please enter a valid age.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Enter your annual income: $";
        if (cin >> userData.annualIncome && userData.annualIncome >= 0)
            break;
        cout << "Invalid input. Please enter a valid income.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Enter your current savings: $";
        if (cin >> userData.currentSavings && userData.currentSavings >= 0)
            break;
        cout << "Invalid input. Please enter a valid savings amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    saveData(userData);
    cout << "Data successfully saved.\n";
}

void viewFinancialAnalysis(const UserData &userData, double annualInflation) {
    cout << "\n=== Financial Analysis ===\n";

    // Retirement
    double retirementTarget = calculateRetirementTarget(userData.age, userData.annualIncome);
    cout << "1. Retirement Savings Target: $" << fixed << setprecision(2) << retirementTarget << endl;

    // Investment
    cout << "\n2. Investment Advice:\n"
         << getInvestmentAdvice(userData.age) << endl;

    // Budget
    cout << "\n3. Monthly Budget:\n";
    calculateBudget(userData.annualIncome / 12);

    // Home Planning
    double housePrice = 500000; // Assumed house price
    int loanTerm = 20;
    double interestRate = 5.0;
    double monthlyPayment = calculateMortgagePayment(housePrice, loanTerm, interestRate);
    cout << "\n4. Home Purchase Planning:\n";
    cout << "   Monthly mortgage payment for a $" << housePrice
         << " house (term " << loanTerm << " years, interest " << interestRate << "%): $"
         << fixed << setprecision(2) << monthlyPayment << endl;

    // Child Education
    double initialTuitionFee = 50000; // Assumed initial tuition fee
    int yearsUntilCollege = 18;
    int collegeDuration = 4;
    double totalEducationCost = calculateEducationCost(initialTuitionFee, yearsUntilCollege, collegeDuration, annualInflation);
    cout << "\n5. Child Education Planning:\n";
    cout << "   Total education cost (college): $" << fixed << setprecision(2) << totalEducationCost << endl;

    // Life Insurance
    int retirementAge = 65;
    double insuranceNeeds = calculateLifeInsuranceNeeds(userData.annualIncome, userData.age, retirementAge);
    cout << "\n6. Life Insurance Needs:\n";
    cout << "   Recommended life insurance amount: $" << fixed << setprecision(2) << insuranceNeeds << endl;

    // Visualization
    vector<double> visualizationData = {
        userData.currentSavings,
        retirementTarget,
        totalEducationCost,
        insuranceNeeds
    };
    vector<string> labels = {
        "Current Savings",
        "Retirement Target",
        "Education Cost",
        "Insurance Needs"
    };
    displayComparisonTable(visualizationData, labels);
}

void viewDataHistory() {
    vector<UserData> dataHistory = readData();
    cout << "\nData History:\n";
    for (const auto &data : dataHistory)
    {
        cout << "Age: " << data.age << ", Income: $" << data.annualIncome
             << ", Savings: $" << data.currentSavings << endl;
    }
}

void simulateScenario(const UserData &userData) {
    double incomeChange;
    cout << "Enter income change percentage (e.g., 10 for 10% increase, -10 for 10% decrease): ";
    cin >> incomeChange;

    UserData scenarioData = userData;
    scenarioData.annualIncome *= (1 + incomeChange / 100);

    cout << "\n=== Scenario Simulation Results ===\n";
    cout << "New income: $" << fixed << setprecision(2) << scenarioData.annualIncome << endl;
    viewFinancialAnalysis(scenarioData, 3.0); // Assume 3% inflation
}

void exportDataToCSV(const UserData &userData) {
    ofstream file("financial_analysis.csv");
    if (file.is_open()) {
        file << fixed << setprecision(0); // Set precision for integers
        
        file << "Category,Value\n";
        file << "Age," << userData.age << "\n";
        file << "Annual Income," << userData.annualIncome << "\n";
        file << "Current Savings," << userData.currentSavings << "\n";
        
        file << setprecision(2); // Set precision to 2 decimal places for financial calculations
        file << "Retirement Target," << calculateRetirementTarget(userData.age, userData.annualIncome) << "\n";
        
        double annualInflation = 3.0;
        double housePrice = 500000;
        int loanTerm = 20;
        double interestRate = 5.0;
        double initialTuitionFee = 50000;
        int yearsUntilCollege = 18;
        int collegeDuration = 4;
        int retirementAge = 65;

        file << "Monthly Mortgage Payment," << calculateMortgagePayment(housePrice, loanTerm, interestRate) << "\n";
        file << "Total Education Cost," << calculateEducationCost(initialTuitionFee, yearsUntilCollege, collegeDuration, annualInflation) << "\n";
        file << "Life Insurance Needs," << calculateLifeInsuranceNeeds(userData.annualIncome, userData.age, retirementAge) << "\n";

        file.close();
        cout << "Data successfully exported to financial_analysis.csv\n";
    } else {
        cout << "Failed to open file for data export.\n";
    }
}

// Add this function to save user data
void saveUserData(const UserData &userData) {
    ofstream file("user_data.txt");
    if (file.is_open()) {
        file << userData.age << "\n";
        file << userData.annualIncome << "\n";
        file << userData.currentSavings << "\n";
        file.close();
        cout << "User data successfully saved.\n";
    } else {
        cout << "Failed to save user data.\n";
    }
}

// Add this function to load user data
bool loadUserData(UserData &userData) {
    ifstream file("user_data.txt");
    if (file.is_open()) {
        file >> userData.age;
        file >> userData.annualIncome;
        file >> userData.currentSavings;
        file.close();
        cout << "User data successfully loaded.\n";
        return true;
    }
    return false;
}

// Add this function to input inflation
double inputInflation() {
    double inflation;
    while (true) {
        cout << "Enter estimated annual inflation rate (%): ";
        if (cin >> inflation && inflation >= 0 && inflation <= 100) {
            return inflation;
        }
        cout << "Invalid input. Please enter a value between 0 and 100.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Add new data structure
struct FinancialGoal {
    string name;
    double target;
    double progress;
    string targetDate;
};

// Add function to add financial goal
void addFinancialGoal(vector<FinancialGoal> &goalList) {
    FinancialGoal goal;
    cout << "Enter financial goal name: ";
    cin.ignore();
    getline(cin, goal.name);
    cout << "Enter target amount ($): ";
    cin >> goal.target;
    cout << "Enter current progress ($): ";
    cin >> goal.progress;
    cout << "Enter target date (DD/MM/YYYY): ";
    cin >> goal.targetDate;
    goalList.push_back(goal);
    cout << "Financial goal successfully added.\n";
}

// Add function to display financial goals
void displayFinancialGoals(const vector<FinancialGoal> &goalList) {
    cout << "\n=== Financial Goals ===\n";
    for (const auto &goal : goalList) {
        cout << "Name: " << goal.name << "\n";
        cout << "Target: $" << fixed << setprecision(2) << goal.target << "\n";
        cout << "Progress: $" << goal.progress << " (" 
             << (goal.progress / goal.target * 100) << "%)\n";
        cout << "Target Date: " << goal.targetDate << "\n\n";
    }
}

// Add function to save financial goals
void saveFinancialGoals(const vector<FinancialGoal> &goalList) {
    ofstream file("financial_goals.txt");
    if (file.is_open()) {
        for (const auto &goal : goalList) {
            file << goal.name << "," << goal.target << "," << goal.progress << "," << goal.targetDate << "\n";
        }
        file.close();
        cout << "Financial goals successfully saved.\n";
    } else {
        cout << "Failed to save financial goals.\n";
    }
}

// Add function to load financial goals
vector<FinancialGoal> loadFinancialGoals() {
    vector<FinancialGoal> goalList;
    ifstream file("financial_goals.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            FinancialGoal goal;
            string temp;
            getline(ss, goal.name, ',');
            getline(ss, temp, ',');
            goal.target = stod(temp);
            getline(ss, temp, ',');
            goal.progress = stod(temp);
            getline(ss, goal.targetDate);
            goalList.push_back(goal);
        }
        file.close();
        cout << "Financial goals successfully loaded.\n";
    }
    return goalList;
}

// Add function to calculate income tax
double calculateIncomeTax(double annualIncome) {
    if (annualIncome <= 50000) {
        return annualIncome * 0.05;
    } else if (annualIncome <= 250000) {
        return 2500 + (annualIncome - 50000) * 0.15;
    } else {
        return 32500 + (annualIncome - 250000) * 0.25;
    }
}

// Add function to create periodic financial report
void createPeriodicFinancialReport(const UserData &userData, const vector<FinancialGoal> &goalList) {
    ofstream file("financial_report.txt");
    if (file.is_open()) {
        file << "=== Periodic Financial Report ===\n\n";
        file << "User Data:\n";
        file << "Age: " << userData.age << "\n";
        file << "Annual Income: $" << fixed << setprecision(2) << userData.annualIncome << "\n";
        file << "Current Savings: $" << userData.currentSavings << "\n\n";

        file << "Financial Goals:\n";
        for (const auto &goal : goalList) {
            file << "- " << goal.name << ": $" << goal.target 
                 << " (Progress: " << (goal.progress / goal.target * 100) << "%)\n";
        }

        file << "\nFinancial Analysis:\n";
        file << "Retirement Target: $" << calculateRetirementTarget(userData.age, userData.annualIncome) << "\n";
        file << "Estimated Income Tax: $" << calculateIncomeTax(userData.annualIncome) << "\n";

        file.close();
        cout << "Financial report successfully created and saved in 'financial_report.txt'.\n";
    } else {
        cout << "Failed to create financial report.\n";
    }
}

// Add function for currency conversion
double convertCurrency(double amount, string from, string to) {
    // Currency exchange rates against USD (example, needs to be updated regularly)
    const double EUR_TO_USD = 0.85;
    const double GBP_TO_USD = 0.73;
    const double JPY_TO_USD = 0.0071;
    const double IDR_TO_USD = 0.000067; // Approximate rate, 1 USD = 15,000 IDR

    double usdAmount;

    if (from == "USD") {
        usdAmount = amount;
    } else if (from == "EUR") {
        usdAmount = amount * EUR_TO_USD;
    } else if (from == "GBP") {
        usdAmount = amount * GBP_TO_USD;
    } else if (from == "JPY") {
        usdAmount = amount * JPY_TO_USD;
    } else if (from == "IDR") {
        usdAmount = amount * IDR_TO_USD;
    } else {
        cout << "Unknown source currency.\n";
        return -1;
    }

    if (to == "USD") {
        return usdAmount;
    } else if (to == "EUR") {
        return usdAmount / EUR_TO_USD;
    } else if (to == "GBP") {
        return usdAmount / GBP_TO_USD;
    } else if (to == "JPY") {
        return usdAmount / JPY_TO_USD;
    } else if (to == "IDR") {
        return usdAmount / IDR_TO_USD;
    } else {
        cout << "Unknown target currency.\n";
        return -1;
    }
}

// Modify main() function to use new features
int main()
{
    cout << R"(
 _____ _                           ____  _                           
|  ___(_)_ __   __ _ _ __   ___ ___|  _ \| | __ _ _ __  _ __   ___ _ __ 
| |_  | | '_ \ / _` | '_ \ / __/ _ \ |_) | |/ _` | '_ \| '_ \ / _ \ '__|
|  _| | | | | | (_| | | | | (_|  __/  __/| | (_| | | | | | | |  __/ |   
|_|   |_|_| |_|\__,_|_| |_|\___\___|_|   |_|\__,_|_| |_|_| |_|\___|_|   
                                                                        
)" << '\n';

    cout << "==================================\n";
    cout << "   Welcome to Finance Planner\n";
    cout << "   Your Personal Financial Assistant\n";
    cout << "==================================\n\n";

    UserData userData;
    if (!loadUserData(userData)) {
        inputNewData(userData);
    }

    double annualInflation = inputInflation();

    vector<FinancialGoal> goalList = loadFinancialGoals();

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                inputNewData(userData);
                saveUserData(userData);
                break;
            case 2:
                viewFinancialAnalysis(userData, annualInflation);
                break;
            case 3:
                viewDataHistory();
                break;
            case 4:
                simulateScenario(userData);
                break;
            case 5:
                exportDataToCSV(userData);
                break;
            case 6:
                addFinancialGoal(goalList);
                saveFinancialGoals(goalList);
                break;
            case 7:
                displayFinancialGoals(goalList);
                break;
            case 8:
                {
                    double tax = calculateIncomeTax(userData.annualIncome);
                    cout << "Estimated Income Tax: $" << fixed << setprecision(2) << tax << endl;
                    cout << "After-Tax Income: $" << (userData.annualIncome - tax) << endl;
                }
                break;
            case 9:
                createPeriodicFinancialReport(userData, goalList);
                break;
            case 10:
                {
                    double amount;
                    string from, to;
                    cout << "Enter amount: ";
                    cin >> amount;
                    cout << "Enter source currency (USD/EUR/GBP/JPY/IDR): ";
                    cin >> from;
                    cout << "Enter target currency (USD/EUR/GBP/JPY/IDR): ";
                    cin >> to;
                    double result = convertCurrency(amount, from, to);
                    if (result != -1) {
                        cout << amount << " " << from << " = " << fixed << setprecision(2) << result << " " << to << endl;
                    }
                }
                break;
            case 11:
                saveUserData(userData);
                saveFinancialGoals(goalList);
                cout << "Data saved successfully. Thank you for using Finance Planner!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}