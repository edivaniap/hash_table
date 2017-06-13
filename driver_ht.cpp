#include <iostream>
#include <functional>
#include <tuple>

#include "hashtbl.h"

using namespace MyHashTable;

// Tipo conta-corrente.
struct Account
{
    //=== Public members
    std::string m_client_name;
    int m_bank_code;
    int m_branch_code;
    int m_acc_number;
    float m_balance;

    //=== Alias
    typedef int AcctKey;

    //=== Special members
    Account( std::string n_ = "<empty>",
            int bnc_ = 1,       // Banco do Brasil.
            int brc_ = 1668,    // Ag. Campus UFRN
            int nmr_ = 0,       // Numero da conta
            float bal_ = 0.f )  // Saldo
        : m_client_name( n_ ),
        m_bank_code( bnc_ ),
        m_branch_code( brc_ ),
        m_acc_number( nmr_ ),
        m_balance( bal_ )
    { /* Empty */ }

    //=== Public interface
    /// Retorna a chave associada com a conta-corrente (Versao 1).
    AcctKey get_key()
    {
        return m_acc_number;
    }

    // DEBUG: Imprime uma formatacao para a conta-corrente.
    inline friend std::ostream &operator<< ( std::ostream & _os, const Account & _acct )
    {
        _os << "[ Client: <" << _acct.m_client_name <<
            "> Bank: <"   << _acct.m_bank_code <<
            "> Branch: <" << _acct.m_branch_code <<
            "> Number: <" << _acct.m_acc_number <<
            "> Balance: <" << _acct.m_balance << "> ]";
        return _os;
    }
};

/// Functor representando a função de dispersão primátia (fp) para a chave (versão 1).
struct KeyHash
{
    std::size_t operator()( const Account::AcctKey & k_ ) const
    {
        // This is just to debug.
        std::cout << ">>> [KeyHash()]: key = " << std::hash< int >()( k_ ) << std::endl;
        // Calcular o valore de dispersao.
        return std::hash< int >()( k_ );
    }
};

/// Functor representando a comparacao entre chaves (versão 1).
struct KeyEqual
{
	bool operator()( const Account::AcctKey & _lhs, const Account::AcctKey & _rhs ) const
	{
		return ( _lhs == _rhs );
		//return ( _lhs.first == _rhs.first && _lhs.second == _rhs.second );
	}
};


int main()
{

/*	Account acct("Alex Bastos", 1, 1668, 54321, 1500.f);

	Account myAccounts[] =
        {
            {"Alex Bastos", 1, 1668, 54321, 1500.f},
            {"Aline Souza", 1, 1668, 45794, 530.f},
            {"Cristiano Ronaldo", 13, 557, 87629, 150000.f},
            {"Jose Lima", 18, 331, 1231, 850.f},
            {"Saulo Cunha", 116, 666, 1, 5490.f}
        };

	// Cria uma tabela de dispersao com capacidade p 23 elementos
	HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas( 23 );

	contas.insert( myAccounts[2].get_key(), myAccounts[2] );
	contas.insert( myAccounts[0].get_key(), myAccounts[0] );
	contas.insert( myAccounts[3].get_key(), myAccounts[3] );
	contas.insert( myAccounts[1].get_key(), myAccounts[1] );
	contas.insert( myAccounts[4].get_key(), myAccounts[4] );

	contas.print();

#ifdef _NOT_NOW
	// Em um segundo momento...
	Account conta1;

	constas.retrieve( myAccounts[2].get_key(), conta1 );
	std::cout << conta1.m_client_name << std::endl;
#endif


	std::cout << ">>> Contas: " << std::endl;	

	for( auto & e : myAccounts )
		std::cout << e << std::endl;

        std::cout << "\n\n>>> Normal exiting...\n";
	return EXIT_SUCCESS;*/
}
