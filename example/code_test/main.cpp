#include <chrono>
#include <iostream>
#include <memory> // unique_ptr<>, std::move()
#include <optional>
#include <random>
#include <vector>

namespace mybank {
    enum class PackageType {
        Saving,
        Loan,
        TimeDeposit
    };

    class Package {
    protected:
        std::string                                        mName;
        float                                              mAmount;
        float                                              mRate;
        int                                                mPeriod;
        std::chrono::time_point<std::chrono::system_clock> mJoinedDate;

    public:
        Package(std::string name, float amount, float rate, int period) {
            mName       = name;
            mAmount     = amount;
            mRate       = rate;
            mJoinedDate = std::chrono::system_clock::now();
            mPeriod     = period;
        }

        virtual ~Package() = default;

        virtual float MaturityAmount(float balance) {
            balance = mAmount + mAmount * mRate * mPeriod / 12;

            return balance;
        }

        std::string Getname() const {
            return mName;
        }

        virtual std::unique_ptr<Package> Clone() const = 0; // 클론, 패키지의 내용을 그대로 복제. = 0 은 "순수가상함수"(컴파일전 반드시 오버라이드 해야함)
    };

    class Saving : public Package {
    private:
        PackageType type = PackageType::Saving;

    public:
        Saving(std::string name, float amount, float rate, int period) : Package(name, amount, rate, period) {
        }

        float MaturityAmount(float balance) override {
            int interest = 0;

            for (int i = 0; i <= mPeriod; i++) {
                interest = balance * mRate * mPeriod * i / 12;
                balance += mAmount + interest;
            }

            return balance;
        }

        std::unique_ptr<Package> Clone() const override { // Saving을 내용따라 복제
            return std::make_unique<Saving>(mName, mAmount, mRate, mPeriod);
        }
    };

    class TimeDeposit : public Package {
    private:
        PackageType type = PackageType::TimeDeposit;

    public:
        TimeDeposit(std::string name, float amount, float rate, int period) : Package(name, amount, rate, period) {
        }

        float MaturityAmount(float balance) override {
            balance = mAmount + mAmount * mRate * mPeriod / 12;

            return balance;
        }

        std::unique_ptr<Package> Clone() const override { // TimeDeposit을 내용따라 복제
            return std::make_unique<TimeDeposit>(mName, mAmount, mRate, mPeriod);
        }
    };

    class Loan : public Package {
    private:
        PackageType type = PackageType::Loan;

    public:
        Loan(std::string name, float amount, float rate, int period) : Package(name, amount, rate, period) {
        }

        float MaturityAmount(float balance) override {
            balance = mAmount * mRate * mPeriod / 12;

            return balance;
        }

        std::unique_ptr<Package> Clone() const override { // Loan 을 내용따라 복제
            return std::make_unique<Loan>(mName, mAmount, mRate, mPeriod);
        }
    };

    class Customer {
    private:
        std::string                           mName;
        int                                   mAge;
        std::string                           mAccountNum;
        float                                 mBalance = 0.0;
        std::vector<std::unique_ptr<Package>> mPackage;

    public:
        Customer(std::string name, int age) : mName(std::move(name)), mAge(age) { // string은 문자의 배열이기에 move를 이용해서 완전히 이동을 시키는 경우가 많음
        }

        Customer(const Customer&)                = delete;  // (고오급 C++ 심화) 복사 기능을 삭제(= delete)
        Customer& operator=(const Customer&)     = delete;  // (고오급 C++ 심화) = 기호를 이용한 복사 기능을 삭제(= delete)
        Customer(Customer&&) noexcept            = default; // (고오급 C++ 심화) 이동 허용(vector가 필요로함)
        Customer& operator=(Customer&&) noexcept = default; // (고오급 C++ 심화) = 기호를 이용한 이동 허용(vector가 필요로함)

        std::string GetAccountNum() const {
            return mAccountNum;
        }

        std::string Getname() const {
            return mName;
        }

        int GetAge() const {
            return mAge;
        }

        float GetBalance() const {
            return mBalance;
        }

        std::vector<std::unique_ptr<Package>>& GetPackage() { // & 있음
            return mPackage;
        }

        const std::vector<std::unique_ptr<Package>>& GetPackage() const { // & 랑 전후로 const 있음
            return mPackage;
        }

        void SetAccountNum(std::string account) {
            mAccountNum = account;
        }

        void PlusBalance(float amount) {
            mBalance += amount;
        }

        void MinusBalance(float amount) {
            mBalance -= amount;
        }

        void JoinPackage(std::unique_ptr<Package> package) { // & 없음, 값으로 받기
            mPackage.push_back(std::move(package));          // 이동 (말그대로 메모리구역(건물)을 뜯어서 이동시킴)
        }

        bool IsEmpty() const {
            if (mPackage.size() == 0) {
                return true;
            }

            return false;
        }
    };

    class Bank {
    private:
        std::string                           mName = "MUBANK";
        std::vector<Customer>                 mCustomers;
        std::vector<std::unique_ptr<Package>> mPackage;

    public:
        Bank() {
        }

        std::string GenerateNewAccountNum() {
            static std::random_device       rd;
            static std::mt19937             gen = std::mt19937(rd());
            std::uniform_int_distribution<> dis(1000, 9999);
            int                             digit          = dis(gen);
            std::string                     account_number = std::to_string(digit);

            return account_number;
        }

        void AddCustomer(std::string name, int age) {                 // & 없음
            mCustomers.emplace_back(name, age);                       // 제일 뒤에 바로 붙이기
            mCustomers.back().SetAccountNum(GenerateNewAccountNum()); // 제일 마지막으로 추가한 고객에게 계좌번호 생성
        }

        void CreateSaving(std::string name, float amount, float rate, int period) {
            mPackage.push_back(std::make_unique<Saving>(name, amount, rate, period));
        }

        void CreateTimeDepsit(std::string name, float amount, float rate, int period) {
            mPackage.push_back(std::make_unique<TimeDeposit>(name, amount, rate, period));
        }

        void CreateLoan(std::string name, float amount, float rate, int period) {
            mPackage.push_back(std::make_unique<Loan>(name, amount, rate, period));
        }

        void Deposit(std::string customer_name, float amount) {
            for (auto& customer : mCustomers) { // & 참조 사용!
                if (customer.Getname() == customer_name) {
                    customer.PlusBalance(amount);
                }
            }
        }

        void Withdraw(std::string customer_name, float amount) {
            for (auto& customer : mCustomers) { // & 참조 사용!
                if (customer.Getname() == customer_name) {
                    customer.MinusBalance(amount);
                }
            }
        }

        void SignPackage(std::string customer_name, std::string name) {
            for (auto& customer : mCustomers) { // & 참조 사용!
                if (customer.Getname() == customer_name) {
                    for (auto& package : mPackage) { // & 참조 사용!
                        if (package->Getname() == name) {
                            customer.JoinPackage(package->Clone()); // 패키지 내용을 복제해서 가입
                        }
                    }
                }
            }
        }

        void PrintCustomerInfo(std::string customer_name) {
            for (auto& customer : mCustomers) { // & 참조 사용!
                if (customer.Getname() == customer_name) {
                    std::cout << "================" << std::endl;
                    std::cout << "나이: " << customer.GetAge() << std::endl;
                    std::cout << "이름: " << customer.Getname() << std::endl;
                    std::cout << "계좌번호: " << customer.GetAccountNum() << std::endl;
                    std::cout << "잔액: " << customer.GetBalance() << std::endl;
                    std::cout << "== 상품 ==============" << std::endl;

                    if (customer.IsEmpty() == true) {

                        std::cout << "가입된 상품이 없습니다." << std::endl;
                    }
                    else {
                        for (auto& package : customer.GetPackage()) {
                            std::cout << "잔액 :" << customer.GetBalance() << std::endl;
                            std::cout << "이자 계산 후:" << package->MaturityAmount(customer.GetBalance()) << std::endl;
                        }
                    }
                }
            }
        }
    };
} // namespace mybank

int main() {
    using namespace mybank;

    Bank mu_bank = Bank();

    mu_bank.CreateLoan("대출1", 500.0, 0.05, 12);
    mu_bank.CreateLoan("대출2", 1000.0, 0.08, 24);
    mu_bank.CreateSaving("적금1", 100.0, 0.04, 6);
    mu_bank.CreateSaving("적금2", 150.0, 0.10, 18);
    mu_bank.CreateTimeDepsit("예금1", 800, 0.06, 12);
    mu_bank.CreateTimeDepsit("예금2", 1500, 0.12, 26);

    mu_bank.AddCustomer("사람A", 20);

    mu_bank.SignPackage("사람A", "적금1");

    mu_bank.PrintCustomerInfo("사람A");
}
