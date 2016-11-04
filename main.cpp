#include "banksystem/BankSystem.h"

using namespace std;

int main() {
    BankSystem newBank = *new BankSystem();
    newBank.startup();
    return 0;
}