find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(bank_account_tests)

target_sources(bank_account_tests
    PRIVATE
    BankAccountTests.cpp
    CheckingAccountTests.cpp
    SavingsAccountTests.cpp
)

target_include_directories(bank_account_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/accounts
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bank_account_tests
    PRIVATE
    accounts
    utils
    accounts
    ${Boost_LIBRARIES}
)