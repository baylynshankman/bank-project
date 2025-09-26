#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(bank_account_suite)

BOOST_AUTO_TEST_CASE(deposit_test){
    SavingsAccount s("first","last", 0.1);

    s.deposit(100);
}

BOOST_AUTO_TEST_SUITE_END()